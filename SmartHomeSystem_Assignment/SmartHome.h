#pragma once

#include "Device.h"
#include <memory>
#include <vector>
#include <string>

using namespace std;

class SmartHome {
private:
    vector<shared_ptr<Device>> DeviceNum;

public:
    void AddDevice(shared_ptr<Device> newDevice);
    bool DeviceName(const string& name) const;
    void RenameDevice();
    void DeviceList() const;
    void Names();
    void Control();
    void Remove();

    void Menu();
    
};

