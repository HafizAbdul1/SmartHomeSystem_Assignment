#pragma once
#include <string>
#include <vector>
#include <functional>

using namespace std;

class Device {
protected:
    string DeviceName;

public:
    Device(const string& name);


    static int AllDevices();
    string getDeviceName() const { return DeviceName; }
    void setDeviceName(const string& name) { DeviceName = name; }
    virtual vector<pair<string, function<void()>>> getCommands() = 0; 
};

