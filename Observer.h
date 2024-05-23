#pragma once
#include <string>
class Observer {
public:
    virtual ~Observer() {}
    virtual void onNotify(const bool event, int typei) = 0;
};