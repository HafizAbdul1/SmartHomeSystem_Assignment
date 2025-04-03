#include "SmartHome.h"
#include <iostream>
#include <algorithm>
#include <memory>
#include "Light.h"
#include "Speaker.h"
#include "TempHumidity.h"
#include "Thermostat.h"
#include "Socket.h"
#include "RadiatorValve.h"
// This is the menu, where everything is put together //
using namespace std;

void SmartHome::AddDevice(shared_ptr<Device> newDevice) { // use of smart pointers
    DeviceNum.push_back(newDevice); // push_back used in order to add new devices
    cout << "Device '" << newDevice->getDeviceName() << "' added." << endl;
}

bool SmartHome::DeviceName(const string& name) const // week 4/5 , constructor inistialisation
{
    return none_of(DeviceNum.begin(), DeviceNum.end(), [&name](const shared_ptr<Device>& device) { //used to match device names//
        //https://www.w3schools.com/cpp/ref_algorithm_none_of.asp#:~:text=The%20none_of%28%29%20function%20tests%20each%20element%20in%20a,The%20range%20of%20data%20is%20specified%20by%20iterators.//
        return device->getDeviceName() == name;
        });
}

void SmartHome::RenameDevice() { 
    //https://www.w3schools.com/cpp/ref_algorithm_find_if.asp  // used to find the device name then change the name.
    string OldName, NewName;

    cout << "Device name: ";
    cin >> OldName;

    auto find = find_if(DeviceNum.begin(), DeviceNum.end(), [&OldName](const shared_ptr<Device>& device) //lambda expression,week 11
        {
        return device->getDeviceName() == OldName;
        });

    if (find != DeviceNum.end()) {
        cout << "Enter new device name: ";
        cin >> NewName;

        if (DeviceName(NewName)) { 
            (*find)->setDeviceName(NewName); // use the iterator to change device name
            cout << "New name: " << NewName << "." << endl;
        }
        else {
            cout << "Error! Please choose a different name." << endl;
        }
    }
    else {
        cout << "Device not found." << endl;
    }
}

void SmartHome::DeviceList() const {
    cout << "Total Devices: " << Device::AllDevices() << endl;
    for (const auto& device : DeviceNum) {
       cout<<device->getDeviceName() << endl; //prints each device name
    }
}

void SmartHome::Names() {
    sort(DeviceNum.begin(), DeviceNum.end(),
        [](const shared_ptr<Device>& a, const shared_ptr<Device>& b) 
        { 
        return a->getDeviceName() < b->getDeviceName(); //compare device names using lambda expression
        });
    cout << "Devices sorted." << endl;
}

void SmartHome::Control() {
    string Name;
    cout << "Device name: " << endl;
    cin >> Name;

    auto control = find_if(DeviceNum.begin(), DeviceNum.end(), 
        [&Name](const shared_ptr<Device>& device) { //lambda expression to find device
        return device->getDeviceName() == Name;
        });

    if (control != DeviceNum.end()) {
        bool Submenu = false;

        do { //list features//
            cout << "Choose from the following for: " << Name << endl;
            auto command = (*control)->getCommands();
            for (size_t i = 0; i < command.size(); ++i) { //iterate commands
                cout << i + 1 << ". " << command[i].first << endl;
            }
            cout << command.size() + 1 << ". Exit Submenu" << endl;

            int DeviceChoice;
            cout << "Enter number: ";
            cin >> DeviceChoice;

            if (DeviceChoice >= 1 && DeviceChoice <= command.size()) {
                command[DeviceChoice - 1].second(); // allow command to happen
            }
            else if (DeviceChoice == command.size() + 1) {
                Submenu = true; 
            }
            else {
                cout << "Error!. Try again." << endl;
            }
        } while (!Submenu);

    }
    else {
        cout << "Device not found." << endl;
    }
}
void SmartHome::Remove() {
    string Name;
    cout << "Enter the name of the device to remove: ";
    cin >> Name;

    auto Remove = find_if(DeviceNum.begin(), DeviceNum.end(), [&Name](const shared_ptr<Device>& device) {
        return device->getDeviceName() == Name;
        });

    if (Remove != DeviceNum.end()) {
        cout << "Removing device '" << Name << "'." << endl;
        DeviceNum.erase(Remove); //removes device from DeviceNum
    }
    else {
        cout << "Device not found." << endl;
    }
}
void SmartHome::Menu() {
    int choice;
    do {
        cout << "Main Menu:" << endl;
        cout << "1. List Devices." << endl;
        cout << "2. Sort by Name." << endl;
        cout << "3. Rename Devices." << endl;
        cout << "4. Control Device." << endl;
        cout << "5. Add Device." << endl;
        cout << "6. Remove Device." << endl;
        cout << "7. Exit." << endl;

        cout << "Enter: ";
        cin >> choice;

        switch (choice) {
        case 1:
            DeviceList();
            break;
        case 2:
            Names();
            break;
        case 3:
            RenameDevice();
            break;
        case 4:
            Control();
            break;
       
        case 5: {
            string name;
            cout << "Enter the new device name: ";
            cin >> name;

            if (DeviceName(name)) {
                cout << "Choose device type:" << endl;
                cout << "1. Light" << endl;
                cout << "2. Temperature & Humidity Sensor" << endl;
                cout << "3. Speaker" << endl;
                cout << "4. Thermostat" << endl;
                cout << "5. Socket" << endl;
                cout << "6. Radiator Valve" << endl;

                int deviceChoice;
                cin >> deviceChoice;

                switch (deviceChoice) {
                   
                case 1:
                    AddDevice(make_shared<Light>(name));
                    break;
                case 2:
                    AddDevice(make_shared<TempHumidity>(name));
                    break;
                case 3:
                    AddDevice(make_shared<Speaker>(name));
                    break;
                case 4:
                    AddDevice(make_shared<Thermostat>(name));
                    break;
                case 5:
                    AddDevice(make_shared<Socket>(name));
                    break;
                case 6:
                    AddDevice(make_shared<RadiatorValve>(name));
                    break;
                default:
                    cout << "Invalid device type!" << endl;
                    break;
                }
            }
            else {
                cout << "Device name already exists. Try again." << endl;
            }
            break;
        }
        case 6:
            Remove();
            break;
    
        case 7:{
             break;
         }
           
            
        default:
            cout << "Enter a valid option (1-7)." << endl;
            break;
        }
    } while (choice != 7);
}
