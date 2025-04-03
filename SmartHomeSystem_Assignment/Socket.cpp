
#include "Socket.h"
#include <iostream>
#include <limits>  
using namespace std;

Socket::Socket(const string& name) : Device(name) {}

vector<pair<string, function<void()>>> Socket::getCommands() {
    return {
        {"Turn " + string(SocketOn ? "OFF" : "ON"), [this]() {
            if (!SocketOn) {
                SocketOn = true;
            }
 else {
  SocketOn = false;
}
cout << "Socket is now " << (SocketOn ? "ON" : "OFF") << "." << endl;
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
{"Adjust Voltage", [this]() {
    if (SocketOn) {
        bool validInput = false;
        while (!validInput) {
            cout << "Enter Voltage (0-140): "; //change voltage power
            cin >> AdjustVolts;

            if (cin.fail() || AdjustVolts < 0 || AdjustVolts > 140) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "Invalid input. Please enter a valid number between 0 and 140." << endl;
            }
else {
 validInput = true;
 cout << "Voltage set to " << AdjustVolts << "V" << endl;
 EnergyUsage = AdjustVolts;  
}
}
}
else {
 cout << "Turn on the Socket first." << endl;
}
}},
{"Display Energy Usage", [this]() {
    DisplayEnergyUsage();
}},
{"Set sleep timer", [this]() {
    cout << "Enter sleep timer (minutes): ";
    cin >> SleepTimer;
    cout << "Sleep timer set to " << SleepTimer << " minutes." << endl;
}}
    };
}

void Socket::SetSchedule(int StartHour, int StartMinute, int EndHour, int EndMinute) {
    auto now = system_clock::now();
    auto today = time_point_cast<seconds>(now);

    StartTime = today + hours(StartHour) + minutes(StartMinute);
    EndTime = today + hours(EndHour) + minutes(EndMinute);

    cout << "Socket scheduled from " << StartHour << ":" << StartMinute << " to "
        << EndHour << ":" << EndMinute << "." << endl;
}

void Socket::CheckSchedule() {
    auto now = system_clock::now();
    if (now >= StartTime && now <= EndTime) {
        if (!SocketOn) {
            SocketOn = true;
            cout << "Schedule: Socket turned ON." << endl;
        }
    }
    else {
        if (SocketOn) {
            SocketOn = false;
            cout << "Schedule: Socket turned OFF." << endl;
        }
    }
}

void Socket::DisplayEnergyUsage() const { //shows live energy usage
    cout << "Live Energy Usage: " << EnergyUsage << " KWH" << endl;
}
