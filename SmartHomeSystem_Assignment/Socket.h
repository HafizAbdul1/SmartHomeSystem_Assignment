#pragma once

#include "Device.h"
#include <chrono>
#include <functional>
#include <vector>

using namespace std;
using namespace chrono;

class Socket : public Device {
private:
    bool SocketOn = false;
    int AdjustVolts = 70;            
    int SleepTimer = 0;              
    system_clock::time_point StartTime;  
    system_clock::time_point EndTime;    
    int EnergyUsage = 0;            

public:
    Socket(const string& name);

    void SetSchedule(int startHour, int startMinute, int endHour, int endMinute);
    void CheckSchedule();
    void DisplayEnergyUsage() const;

    vector<pair<string, function<void()>>> getCommands() override;
};

