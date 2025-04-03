#include "RadiatorValve.h"
#include "GlobalVariables.h"  
#include <iostream>
#include <limits>

using namespace std;

RadiatorValve::RadiatorValve(const string& name) : Device(name) {}



vector<pair<string, function<void()>>> RadiatorValve::getCommands() {
    return {
        {"Turn " + string(RadiatorOn ? "OFF" : "ON"), [this]() {
            if (!RadiatorOn) {
                RadiatorOn = true;
            }
 else {
  RadiatorOn = false;
}
cout << "Radiator is now " << (RadiatorOn ? "ON" : "OFF") << "." << endl;
}},
{"Set schedule", [this]() {
    int StartHour, StartMinute, EndHour, EndMinute;
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
{"Check Temperature", [this]() {
    cout << "Current Temperature is: " << AdjustTemp << "C" << endl;  
}},
{"Adjust Temperature", [this]() {
    if (RadiatorOn) {
        bool validInput = false;
        while (!validInput) {
            cout << "Enter Temperature (0-30): ";
            cin >> AdjustTemp;  

            if (cin.fail() || AdjustTemp < 0 || AdjustTemp > 30) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "ERROR! Please enter a valid number between 0 and 30." << endl;
            }
else {
 validInput = true;
 cout << "Temperature set to " << AdjustTemp << "C" << endl;  
}
}
}
else {
 cout << "Turn on the Radiator first." << endl;
}
}},
{"Set sleep timer", [this]() {
    cout << "Enter sleep timer (minutes): ";
    cin >> SleepTimer;
    cout << "Sleep timer set to " << SleepTimer << " minutes." << endl;
}}
    };
}

void RadiatorValve::SetSchedule(int StartHour, int StartMinute, int EndHour, int EndMinute) {
    auto now = system_clock::now();
    auto today = time_point_cast<seconds>(now);

    StartTime = today + hours(StartHour) + minutes(StartMinute);
    EndTime = today + hours(EndHour) + minutes(EndMinute);

    cout << "Radiator scheduled from " << StartHour << ":" << StartMinute << " to "
        << EndHour << ":" << EndMinute << "." << endl;
}

void RadiatorValve::CheckSchedule() {
    auto now = system_clock::now();
    if (now >= StartTime && now <= EndTime) {
        if (!RadiatorOn) {
            RadiatorOn = true;
            cout << "Schedule: Radiator turned ON." << endl;
        }
    }
    else {
        if (RadiatorOn) {
            RadiatorOn = false;
            cout << "Schedule: Radiator turned OFF." << endl;
        }
    }
}
