#include "TempHumidity.h"
#include "GlobalVariables.h"
#include <iostream>

using namespace std;

TempHumidity::TempHumidity(const string& name) : Device(name) {}



void TempHumidity::UpdateHumidity() { // humidity updates with temp
    if (AdjustTemp > 25) {
        Humidity = 45;
    }
    else if (AdjustTemp > 20) {
        Humidity = 40;
    }
    else if (AdjustTemp > 15) {
        Humidity = 33;
    }
    else if (AdjustTemp > 10) {
        Humidity = 15;
    }

    SaveData(); 
}

void TempHumidity::SaveData() {
    history.emplace_back(AdjustTemp, Humidity);
    //when 
    //when temperature gets updated current temp and h get added to data collection //https://www.geeksforgeeks.org/vector-emplace-function-in-c-stl/
}

void TempHumidity::ShowData() const {
    cout << "Temperature & Humidity Data:" << endl;
        for (size_t i = 0; i < history.size(); ++i) {
            cout << "Temperature = " << history[i].first << " C" << endl;
            cout << "Humidity = " << history[i].second << " %" << endl;
            cout << "No data available." << endl;
        }
    }

vector<pair<string, function<void()>>> TempHumidity::getCommands() {
    return {
        {"Show Data (Must press '(2) Update Humidity' first,for updated results.)", [this]() { ShowData(); }},
        {"Update Humidity", [this]() { UpdateHumidity(); }}  

    };
}


