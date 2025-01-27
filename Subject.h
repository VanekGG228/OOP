#pragma once
#include <vector>

#include "Observer.h"

class Subject {
public:
    void addObserver(Observer* observer);

    void removeObserver(Observer* observer);

protected:
    void notify(const bool event, int type);

private:
    std::vector<Observer*> observers;
};

