#pragma once
#include "IAudioDevice.hpp"
#include "../models/Song.hpp"
#include "../external/HeadphoneApi.hpp"

class HeadPhoneAdapter : public IAudioDevice {
private:
    HeadphonesAPI* bluetoothApi;
public:
    HeadPhoneAdapter(HeadphonesAPI* bluetoothApi) {
        this -> bluetoothApi = bluetoothApi;
    }

    void playSound(Song *song) override {
        string payload = "Playing song: " + song -> getTitle() + " by " + song -> getArtist();
        bluetoothApi -> playSoundViaJack(payload);
    }
};