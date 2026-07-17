#pragma once
#include "IAudioDevice.hpp"
#include "../models/Song.hpp"
#include "../external/BluetoothApi.hpp"

class BluetoothAdapter : public IAudioDevice {
private:
    BluetoothApi* bluetoothApi;
public:
    BluetoothAdapter(BluetoothApi* bluetoothApi) {
        this -> bluetoothApi = bluetoothApi;
    }

    void playSound(Song *song) override {
        string payload = "Playing song: " + song -> getTitle() + " by " + song -> getArtist();
        bluetoothApi -> playSoundViaBluetooth(payload);
    }
};