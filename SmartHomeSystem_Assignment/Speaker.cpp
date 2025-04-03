#include "Speaker.h"
#include <iostream>
using namespace std;

Speaker::Speaker(const string& name) : Device(name) {}

vector<pair<string, function<void()>>> Speaker::getCommands() {
    return {
        {"Turn " +string(SpeakerOn ? "OFF" : "ON"), [this]() {
            SpeakerOn = !SpeakerOn;
            cout << "Speakers are now " << ( SpeakerOn ? "ON" : "OFF") << "." << endl;
        }},
        {"Adjust Volume", [this]() {
            if (SpeakerOn) {
                cout << " Current Volume: " << Decibals << " decibels." << endl;
                cout << " Volume (0-100): ";
                cin >> Decibals;
                if (Decibals >= 0 && Decibals <= 100) {
                   cout << "Volume set to " << Decibals << "%." << endl;
                }
 else {
  cout << "Error! Volume must be between 0-100." << endl;
}
}
 else {
 cout << "Error! SPEAKERS ARE SWITCHED OFF." << endl;
}
}},
{"Set Sleep Timer", [this]() {
    cout << "Enter sleep timer (minutes): ";
    cin >> SleepTimer;
    if (SleepTimer >0) {
        cout << "Sleep timer set to " << SleepTimer << " minutes." << endl;
    }
else {
  cout << "Error! Timer must be over 0!." << endl;
}
}},
{"Exit Speaker Device", []() {
    cout << "Exiting Speaker Device menu." << endl;
}}
    };
}
