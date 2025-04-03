#pragma once

#include "Device.h"
#include <iostream>
using namespace std;

class Speaker : public Device {
private:
    bool SpeakerOn = false;
    int Decibals = 50;
    int SleepTimer = 0;

public:
    Speaker(const string& name);

   vector<pair<string, function<void()>>> getCommands() override;
};


