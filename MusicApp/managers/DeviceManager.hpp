#pragma once
#include<iostream>
#include "../device/IAudioDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../factories/DeviceFactory.hpp"

using namespace std;

class DeviceManager {
private:
    static DeviceManager* instance;
    IAudioDevice* currentAudioDevice;
    DeviceManager() {
        currentAudioDevice = nullptr;
    }
public:
    static DeviceManager* getInstance() {
        if (instance == nullptr) {
            instance = new DeviceManager();
        }
        return instance;
    }
    void connect(DeviceType deviceType) {
        if (currentAudioDevice) {
            delete currentAudioDevice;
        }

        currentAudioDevice = DeviceFactory::createAudioDevice(deviceType);

        switch(deviceType) {
            case DeviceType::BLUETOOTH:
                cout<< "Bluetooth device connected \n";
                break;
            case DeviceType::SPEAKER:
                cout<< "Speaker device connected \n";
                break;
            case DeviceType::HEADPHONES:
                cout<< "Headphones connected \n";
        }
    }

    IAudioDevice* getAudioDevice() {
        if (!currentAudioDevice) {
            throw runtime_error("No audio device is connected.");
        }
        return currentAudioDevice;
    }

    bool hasAudioDevice() {
        return currentAudioDevice != nullptr;
    }
};

DeviceManager* DeviceManager::instance = nullptr;