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

class StatisticObserver: public Observer{

};