#pragma once
#include <iostream>
#include "../device/IAudioDevice.hpp"
#include "../enums/DeviceType.hpp"
#include "../device/BluetoothAdapter.hpp"
#include "../device/SpeakerAdapter.hpp"
#include "../device/HeadPhoneAdapter.hpp"

using namespace std;

class DeviceFactory {
    public:
        static IAudioDevice* createAudioDevice(DeviceType type) {
            switch(type) {
                case DeviceType::BLUETOOTH:
                    return new BluetoothAdapter(new BluetoothApi());
                case DeviceType::SPEAKER:
                    return new SpeakerAdapter(new SpeakerAPI());
                case DeviceType::HEADPHONES:
                    return new HeadPhoneAdapter(new HeadphonesAPI());
                default:
                    throw invalid_argument("Invalid device type");
            }
        }
};