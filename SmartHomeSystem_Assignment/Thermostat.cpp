#include "Thermostat.h"
#include <iostream>

using namespace std;
using namespace chrono;

Thermostat::Thermostat(const string& name) : Device(name) {}

// https://www.geeksforgeeks.org/chrono-in-c/ // how i learnt to use chrono

void Thermostat::SetSchedule(int StartHour, int StartMinute, int EndHour, int EndMinute) { 
    auto now = system_clock::now(); // current time
    auto today = time_point_cast<seconds>(now); // current time (seconds)

   
    StartTime = today + hours(StartHour) + minutes(StartMinute); // Start time, adds the hours and minutes to today
    EndTime = today + hours(EndHour) + minutes(EndMinute); //end time, add the hours and minutes to today

    cout << "Thermostat scheduled from " << StartHour << ":" << StartMinute << " to " << EndHour << ":" << EndMinute << "." << endl;
}

void Thermostat::CheckSchedule() {
    auto now = system_clock::now();
    if (now >= StartTime && now <= EndTime) { //checks current time
        if (!ThermoON) {
            ThermoON = true; // if true schedule starts
            cout << "Schedule: Thermostat turned ON" << endl;
        }
    }
    else {
        if (ThermoON) {
            ThermoON = false; //else 
            cout << "Schedule: Thermostat turned OFF." << endl;
        }
    }
}

vector<pair<string, function<void()>>> Thermostat::getCommands() {
    return {
        {"Turn " + string(ThermoON ? "OFF" : "ON"), [this]() {
            ThermoON = !ThermoON;
            cout << "Thermostat is now " << (ThermoON ? "ON" : "OFF") << endl;
        }},
        {"Set schedule", [this]() {
            int StartHour, StartMinute, EndHour,EndMinute;
            cout << "Enter start time (hour, 0-23): ";
            cin >> StartHour;
            cout << "Enter start time (minute, 0-59): ";
            cin >> StartMinute;
            cout << "Enter end time (hour, 0-23): ";
            cin >> EndHour;
            cout << "Enter end time (minute, 0-59): ";
            cin >> EndMinute;

            SetSchedule(StartHour, StartMinute, EndHour, EndMinute);
        }},
        {"Enable Heating Boost", [this]() {
            HeatingBoost = !HeatingBoost; // heating boost on
            cout << "Heating Boost is " << (HeatingBoost ? "ON" : "OFF") << "for 60 minutes. "<<endl;
        }}
    };
}
