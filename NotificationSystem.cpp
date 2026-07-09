#include<bits/stdc++.h>
#include <mutex>
using namespace std;


//Decorator Pattern
class INotification {
    public:
        virtual string getContent() = 0;
        ~INotification() = default;
};

class SimpleNotification : public INotification {
    string content;
    public:
        SimpleNotification(string content) {
            this -> content = content;
        }

        string getContent() override {
            return content;
        }
        
};

class IDecorator : public INotification {
    public:
        virtual string getContent() = 0;
    ~IDecorator() = default;
};

class BoldDecorator : public IDecorator {
    INotification* notification;
    public:
        BoldDecorator(INotification* notification) {
            this -> notification = notification;
        }
        string getContent() override {
            return "<b>" + notification -> getContent() + "</b>";
        }
};

class TimeStampDecorator : public IDecorator {
    INotification* notification;
    public:
        TimeStampDecorator(INotification* notification) {
            this -> notification = notification;
        }
        string getContent() override {
            time_t now = time(0);
            char* dt = ctime(&now);
            return string(dt) + " " + notification -> getContent();
        }
};
//--------------------
//Observer Pattern

class IObserver {
    public:
        virtual void update() = 0;
};

class IObservable {
    public:
        virtual void addObserver(IObserver* observer) = 0;
        virtual void removeObserver(IObserver* observer) = 0;
        virtual void notifyObservers() = 0;
};



class NotificationOberservable : public IObservable {
    vector<IObserver*> observers;
    INotification* notification;
    public:
        NotificationOberservable() {
            this -> notification = nullptr;
        }
        void addObserver(IObserver* observer) override {
            observers.push_back(observer);
        }
        void removeObserver(IObserver* observer) override {
            observers.erase(remove(observers.begin() , observers.end() , observer) , observers.end());
        }
        void notifyObservers() override {
            for (auto observer : observers) {
                observer -> update();
            }
        }

        void setNotification(INotification* notification) {
            if (this -> notification != nullptr) {
                delete this -> notification;
            }
            this -> notification = notification;
            notifyObservers();
        }

        INotification* getNotification() {
            return notification;
        }

        string getNotificationContent() {
            if(notification != nullptr) {
                return notification -> getContent();
            }
            return "";
        }

        ~NotificationOberservable() {
            if (notification != nullptr) {
                delete notification;
            }
        }
};

//--------------------
//Singleton Pattern
class NotificationService {
private:
    NotificationOberservable* observable;
    static NotificationService* instance;
    vector<INotification*> notifications;
    static std::mutex mtx;
    NotificationService() {
        observable = new NotificationOberservable();
    }
public:
    static NotificationService* getInstance() {
        {
            lock_guard<std::mutex> lock(mtx);

            if(instance == nullptr){
                instance = new NotificationService();
            }
        }

        return instance;
    }

    NotificationOberservable* getObservable() {
        return observable;
    }

    void sendNotification(INotification* notification) {
        notifications.push_back(notification);
        observable -> setNotification(notification);
    }

    
};

NotificationService* NotificationService::instance = nullptr;
std::mutex NotificationService::mtx;

class Logger : public IObserver {
    NotificationOberservable* observable;
    public:
        Logger() {
            this -> observable = NotificationService::getInstance() -> getObservable();
            observable -> addObserver(this);
        }

        void update() override {
            cout << "Logger: New notification received: " << observable -> getNotificationContent() << endl;
            cout << endl;
        }
};

//Strategy Pattern
class INotificationStrategy {
    public:
        virtual void sendNotification(string content) = 0;
        ~INotificationStrategy() = default;
};

class EmailStrategy : public INotificationStrategy {
    private:
        string emailId;
    public:
        EmailStrategy(string emailId) {
            this -> emailId = emailId;
        }

        void sendNotification(string content) override {
            cout << "Sending Email to " << emailId << " with content: " << content << endl;
            cout << endl;
        }
};

class SMSStrategy : public INotificationStrategy {
    private:
        string phoneNumber;
    public:
        SMSStrategy(string phoneNumber) {
            this -> phoneNumber = phoneNumber;
        }

        void sendNotification(string content) override {
            cout << "Sending SMS to " << phoneNumber << " with content: " << content << endl;
            cout << endl;
        }
};

class PopUpStrategy : public INotificationStrategy {
    public:
        void sendNotification(string content) override {
            cout << "Showing PopUp with content: " << content << endl;
            cout << endl;
        }
};

class NotificationEngine : public IObserver{
    NotificationOberservable* observable;
    vector<INotificationStrategy*> strategies;
    public:
        NotificationEngine() {
            this -> observable = NotificationService::getInstance() -> getObservable();
            observable -> addObserver(this);
        }

        void addStrategy(INotificationStrategy* strategy) {
            strategies.push_back(strategy);
        }

        void update() override {
            string content = observable -> getNotificationContent();
            for (auto strategy : strategies) {
                strategy -> sendNotification(content);
            }
        }
};

int main() {
    NotificationService* notificationService = NotificationService::getInstance();
    Logger* logger = new Logger();

    NotificationEngine* notificationEngine = new NotificationEngine();
    notificationEngine -> addStrategy(new EmailStrategy("random@example.com"));
    notificationEngine -> addStrategy(new SMSStrategy("+1234567890"));
    notificationEngine -> addStrategy(new PopUpStrategy());

    INotification* notification = new SimpleNotification("Your order has been shipped!");
    notification = new BoldDecorator(notification);
    notification = new TimeStampDecorator(notification);

    notificationService -> sendNotification(notification);

    delete logger;
    delete notificationEngine;
    return 0;
}

