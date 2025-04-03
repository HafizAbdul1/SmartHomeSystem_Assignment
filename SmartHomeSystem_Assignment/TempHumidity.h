#pragma once
#include "Device.h"
#include <vector>
#include <functional>
#include <iostream>

class TempHumidity : public Device {
private:
    int Humidity = 15;
    vector<pair<int, int>> history;

public:
    TempHumidity(const string& name);

    void UpdateHumidity();
    void SaveData();
    void ShowData() const;
 
    vector<pair<string, function<void()>>> getCommands() override; 
};
