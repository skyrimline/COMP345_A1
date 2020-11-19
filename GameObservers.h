#pragma once
#include <iostream>
#include <list>

using namespace std;

class GameEngine;

class Observer {
        public:
            ~Observer();
            virtual void Update() = 0;
        protected:
            Observer();
};


class Subject {
    public:
        virtual void Attach(Observer* o);
        virtual void Detach(Observer* o);
        virtual void Notify();
        Subject();
        ~Subject();
    private:
        list<Observer*>* _observers;
};


class PhaseObserver : public Observer {
public:
    PhaseObserver();
    PhaseObserver(GameEngine* ge);
    ~PhaseObserver();
    void Update();
    void display();

private:
     GameEngine *_subject;
};


//class PhaseView : public Subject {
//public:
//    PhaseView();
//    ~PhaseView();
//
//private:
//
//};