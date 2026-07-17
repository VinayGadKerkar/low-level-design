#include<bits/stdc++.h>
using namespace std;

class Walkable {
    public:
        virtual void walk() = 0;
};

class Talkable {
    public:
        virtual void talk() = 0;
};

class Flyable {
    public:
        virtual void fly() = 0;
};

class NormalTalk : public Talkable {
    public:
        void talk() override {
            cout << "Talking normally" << endl;
        }
};

class NoTalk : public Talkable {
    public:
        void talk() override {
            cout << "Not talking" << endl;
        }
};

class NormalWalk : public Walkable {
    public:
        void walk() override {
            cout << "Walking normally" << endl;
        }
};

class NoWalk : public Walkable {
    public:
        void walk() override {
            cout << "Not Walking" << endl;
        }
};

class NormalFly : public Flyable {
    public:
        void fly() override {
            cout << "Flying Normally" <<endl;
        }
};

class NoFly : public Flyable {
    public:
        void fly() override {
            cout << "Not Flying" << endl;
        }
};

class Robot {
    Walkable* walkBehaviour;
    Talkable* talkBehaviour;
    Flyable* flyBehaviour;
    public:
        Robot(Walkable* walkType , Talkable* talkType , Flyable* flyType){
            this -> walkBehaviour = walkType;
            this -> talkBehaviour = talkType;
            this -> flyBehaviour = flyType;
        }
        void walk() {
            walkBehaviour -> walk();
        }
        void talk() {
            talkBehaviour -> talk();
        }
        void fly() {
            flyBehaviour -> fly();
        }
        virtual void projection() = 0;      
};

class CompanionRobot : public Robot {
    public:
        CompanionRobot(Walkable* w , Talkable* t , Flyable* f) : Robot(w , t , f) {}
        void projection() override {
            cout << "Displaying friendly companion features..." << endl;
            cout << "Displaying worker efficiency stats..." << endl;
        }
};

class WorkerRobot : public Robot {
    public:
        WorkerRobot(Walkable* w , Talkable* t , Flyable* f) : Robot(w , t , f) {}
        void projection() override {
            cout << "Displaying worker efficiency stats..." << endl;
        }
};


int main(){
    Robot* r1 = new CompanionRobot(new NormalWalk()  , new NormalTalk() , new NoFly());
    r1 -> walk();
    r1 -> talk();
    r1 -> fly();
    cout << "-----------------------------" << endl;
    Robot* r2 = new WorkerRobot(new NoWalk() , new NoTalk() , new NormalFly());
    r2 -> walk();
    r2 -> talk();
    r2 -> fly();

    return 0;
}