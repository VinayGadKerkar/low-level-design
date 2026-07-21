#include<iostream>
using namespace std;

struct PaymentRequest {
    string receiver;
    string sender;
    double amount;
    string currency;

    PaymentRequest(const string& sender , const string &receiver , double amount , const string &currency){
        this -> receiver = receiver;
        this -> sender = sender;
        this -> amount = amount;
        this -> currency = currency;
    }
};

class BankingSystem {
    public:
        virtual bool processPayment(double amount) = 0;
        ~BankingSystem() {}
};

class PaytmBankingSystem : public BankingSystem {
    public:
        PaytmBankingSystem() {}

        bool processPayment(double amount) override {
            cout << "[Paytm] Processing amount :" << amount << endl; 
            int x = rand() % 100;
            return x < 10;
        }
};

class RazorPayBankingSystem : public BankingSystem {
    public:
        RazorPayBankingSystem() {}

        bool processPayment(double amount) override {
            cout << "[RazorPay] Processing amount :" << amount << endl; 
            int x = rand() % 100;
            return x < 90;
        }
};

class PaymentGateway {
    protected:
        BankingSystem* bankingSystem;
    public:
        PaymentGateway() {
            bankingSystem = nullptr;
        }
        virtual ~PaymentGateway(){
            delete bankingSystem;
        }
        virtual bool processPayment(PaymentRequest* request){
            if(!validate(request)){
                cout << "[PaymentGateway] Validation failed" << request -> sender << endl;
                return false;
            }
            if(!initialize(request)){
                cout << "[PaymentGateway] Validation failed" << request -> sender << endl;
                return false;
            }
            if(!confirm(request)){
                cout << "[PaymentGateway] Validation failed" << request -> sender << endl;
                return false;
            }

            return true;
        }
        virtual bool validate(PaymentRequest* request) = 0;
        virtual bool initialize(PaymentRequest* request) = 0;
        virtual bool confirm(PaymentRequest* request) = 0;
};

class RazorPayGateWay : public PaymentGateway {
    public:
        RazorPayGateWay(){
            bankingSystem = new RazorPayBankingSystem();
        }

        bool validate(PaymentRequest* request) override {
            cout << "[Razorpay] Validating payment for " << request->sender << ".\n";

            if (request->amount <= 0)
                return false;
            
            return true;
        }

        bool initialize(PaymentRequest* request) override {
            cout << "[Razorpay] Initiating payment of " << request->amount 
                  << " " << request->currency << " for " << request->sender << ".\n";

            return bankingSystem->processPayment(request->amount);
        }

        bool confirm(PaymentRequest* request) override {
            cout << "[Razorpay] Confirming payment for " << request->sender << ".\n";

        // Confirmation always succeeds in this simulation
            return true;
        }
};

class PaytmGateway : public PaymentGateway {
    public:
        PaytmGateway(){
            bankingSystem = new PaytmBankingSystem();
        }

        bool validate(PaymentRequest* request) override {
            cout << "[Paytm] Validating payment for " << request->sender << ".\n";

            if (request->amount <= 0)
                return false;
            
            return true;
        }

        bool initialize(PaymentRequest* request) override {
            cout << "[Paytm] Initiating payment of " << request->amount 
                  << " " << request->currency << " for " << request->sender << ".\n";

            return bankingSystem->processPayment(request->amount);
        }

        bool confirm(PaymentRequest* request) override {
            cout << "[Paytm] Confirming payment for " << request->sender << ".\n";

        // Confirmation always succeeds in this simulation
            return true;
        }
};

class PaymentGatewayProxy : public PaymentGateway {
    private:
        int retries;
        PaymentGateway* realGateway;
    public:
        PaymentGatewayProxy(PaymentGateway* gateway , int maxRetries){
            realGateway = gateway;
            retries = maxRetries;
        }
        ~PaymentGatewayProxy () {
            delete realGateway;
        }
        
        bool processPayment(PaymentRequest* request) override {
            bool result = false;
            for (int attempt = 0; attempt < retries; ++attempt) {
                if (attempt > 0) {
                    cout << "[Proxy] Retrying payment (attempt " << (attempt+1)
                          << ") for " << request->sender << ".\n";
                }
                result = realGateway->processPayment(request);
                if (result) break;
            }
            if (!result) {
                cout << "[Proxy] Payment failed after " << (retries)
                      << " attempts for " << request->sender << ".\n";
            }
            return result;
        }

        bool validate(PaymentRequest* request) override {
            return realGateway -> validate(request);
        }

        bool initialize(PaymentRequest* request) override {
            return realGateway -> initialize(request);
        }

        bool confirm(PaymentRequest* request) override {
            return realGateway -> confirm(request);
        }
};

enum class GatewayType {
    PAYTM , 
    RAZORPAY
};

class GatewayFactory {
    private:
        static GatewayFactory instance;
        GatewayFactory(){}
        GatewayFactory(const GatewayFactory&) = delete;
        GatewayFactory& operator = (const GatewayFactory&) = delete;
    public:
        static GatewayFactory& getInstance() {
            return instance;
        }

        PaymentGateway* getGateway(GatewayType type){
            if(type == GatewayType::PAYTM){
                PaymentGateway* paymentGateway = new PaytmGateway();
                return new PaymentGatewayProxy(paymentGateway , 3);
            }else{
                PaymentGateway* paymentGateway = new RazorPayGateWay();
                return new PaymentGatewayProxy(paymentGateway , 2);

            }
        }
};

GatewayFactory GatewayFactory::instance;

class PaymentService {
    private:
        static PaymentService instance;
        PaymentGateway* gateway;

        PaymentService(){
            gateway = nullptr;
        }
        ~PaymentService(){
            delete gateway;
        }
        PaymentService(const PaymentService&) = delete;
        PaymentService& operator=(const PaymentService&) = delete;

    public:
        static PaymentService& getInstance(){
            return instance;
        }

        void setGateway(PaymentGateway* g){
            if(gateway) delete gateway;
            gateway = g;
        }

        bool processPayment(PaymentRequest* request) {
            if(!gateway) {
                cout << "[PaymentService] No Payment gateway selected.\n";
                return false;
            }
            return gateway -> processPayment(request);
        }
};

PaymentService PaymentService::instance;

class PaymentController {
    private:
        static PaymentController instance;
        PaymentController() {}
        PaymentController(const PaymentController&) = delete;
        PaymentController& operator=(const PaymentController&) = delete;
    public:
        static PaymentController& getInstance() {
            return instance;
        }
        bool handlePayment(GatewayType type , PaymentRequest* req){
            PaymentGateway* paymentGateway = GatewayFactory::getInstance().getGateway(type);
            PaymentService::getInstance().setGateway(paymentGateway);
            return PaymentService::getInstance().processPayment(req);
        }
};

PaymentController PaymentController::instance;

int main() {
    srand(static_cast<unsigned>(time(nullptr)));
    PaymentRequest* req1 = new PaymentRequest("Aditya", "Shubham", 1000.0, "INR");

    cout << "Processing via Paytm\n";
    cout << "------------------------------\n";
    bool res1 = PaymentController::getInstance().handlePayment(GatewayType::PAYTM, req1);
    cout << "Result: " << (res1 ? "SUCCESS" : "FAIL") << "\n";
    cout << "------------------------------\n\n";

    PaymentRequest* req2 = new PaymentRequest("Shubham", "Aditya", 500.0, "USD");

    cout << "Processing via Razorpay\n";
    cout << "------------------------------\n";
    bool res2 = PaymentController::getInstance().handlePayment(GatewayType::RAZORPAY, req2);
    cout << "Result: " << (res2 ? "SUCCESS" : "FAIL") << "\n";
    cout << "------------------------------\n";

    return 0;
}
