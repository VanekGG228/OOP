#pragma once
#include <vector>

#include "Observer.h"

class Subject {
public:
    void addObserver(Observer* observer) {
        observers.push_back(observer);
    }

    void removeObserver(Observer* observer) {
        observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
    }

protected:
    void notify(const bool event,int type) {
        for (Observer* observer : observers) {
            observer->onNotify(event, type);
        }
    }

private:
    std::vector<Observer*> observers;
};

