#pragma once
#include "IAudioDevice.hpp"
#include "../models/Song.hpp"
#include "../external/SpeakerApi.hpp"

class SpeakerAdapter : public IAudioDevice {
private:
    SpeakerAPI* speakerApi;
public:
    SpeakerAdapter(SpeakerAPI* speakerApi) {
        this -> speakerApi = speakerApi;
    }

    void playSound(Song *song) override {
        string payload = "Playing song: " + song -> getTitle() + " by " + song -> getArtist();
        speakerApi -> playSoundViaCable(payload);
    }
};