#pragma once

#include <vector>

using namespace std;

class Observer
{
public:
    virtual void update() = 0;
};

class Observable
{
public:
    void addObserver(Observer* obs)
    {
        observers.push_back(obs);
    }

    void notifyObservers()
    {
        for (auto& obs: observers)
        {
            obs->update();
        }   
    }
private:
    vector<Observer*> observers;
};
