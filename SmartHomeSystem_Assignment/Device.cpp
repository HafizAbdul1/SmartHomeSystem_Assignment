#include "Device.h"
#include <iostream>

using namespace std;


static int Devices = 0;

Device::Device(const string& name) : DeviceName(name) {
    Devices++; 
}

int Device::AllDevices() {
    return Devices;
}
