#include "Light.h"
#include <iostream>

using namespace std;

Light::Light(const string& name) : Device(name) {}



vector<pair<string, function<void()>>> Light::getCommands() {
    return {
        {"Turn " + string(LightsOn ? "OFF" : "ON"), [this]() { // switch lights on and off 
            LightsOn = !LightsOn;
            cout << "Lights are now " << (LightsOn ? "ON" : "OFF") << "." << endl;
        }},
        {"Adjust brightness", [this]() {
            if (LightsOn) {
                cout << "Enter brightness (0-100): ";
                cin >> AdjustBrightness;
                cout << "Brightness set to " << AdjustBrightness << "%." << endl;
            }
 else {
  cout << "Error! LIGHTS ARE SWITCHED OFF." << endl;
}
}},
{"Set sleep timer", [this]() {
    cout << "Enter sleep timer (minutes): ";
    cin >> SleepTimer;
    cout << "Sleep timer set to " << SleepTimer << " minutes." << endl;
}},
{"Exit Light Device", []() {
    cout << "Exiting Light Device menu." << endl;
}}
    };
}
