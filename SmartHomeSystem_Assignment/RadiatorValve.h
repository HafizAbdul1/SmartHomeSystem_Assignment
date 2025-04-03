#pragma once

#include "Device.h"
#include <chrono>
#include <functional>
#include <vector>

using namespace std;
using namespace chrono;

class RadiatorValve : public Device {
private:
    bool RadiatorOn = false;
    int SleepTimer = 0;

    system_clock::time_point StartTime;
    system_clock::time_point EndTime;

public:
    RadiatorValve(const string& name);

    void SetSchedule(int StartHour, int StartMinute, int EndHour, int EndMinute);
    void CheckSchedule();
    vector<pair<string, function<void()>>> getCommands() override;
};


