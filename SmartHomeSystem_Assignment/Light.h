#pragma once
#include "Device.h"
#include <vector>
#include <functional>
#include <string>

using namespace std;

class Light : public Device {
private:
    bool LightsOn = false;
    int AdjustBrightness = 100;
    int SleepTimer = 0;

public:
    Light(const string& name); //constructor initialisation

    vector<pair<string, function<void()>>> getCommands() override; //overloading
};

