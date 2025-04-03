#pragma once

#include "Device.h"
#include <chrono>
#include <functional>
#include <vector>

using namespace std;
using namespace chrono;

class Thermostat : public Device {
private:
    bool ThermoON = false;
    bool HeatingBoost = false;
    system_clock::time_point StartTime;  
    system_clock::time_point EndTime;  

public:
    Thermostat(const string& name);

    void SetSchedule(int StartHour, int StartMinute, int EndHour, int EndMinute);
    void CheckSchedule();

    vector<pair<string, function<void()>>> getCommands() override;
};


