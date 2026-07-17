#pragma once
#include "../models/Song.hpp"
#include "../device/IAudioDevice.hpp"
#include<string>
#include<iostream>

using namespace std;

class AudioEngine {
private:
    Song* currentSong;
    bool songIsPaused;
public:
    AudioEngine() {
        currentSong = nullptr;
        songIsPaused = false;
    }
    string getCurrentSongTitle() const {
        if (currentSong) {
            return currentSong->getTitle();
        }
        return "";
    }
    bool isPaused() const {
        return songIsPaused;
    }
    void play(IAudioDevice* aod, Song* song) {
        if (song == nullptr) {
            throw runtime_error("Cannot play a null song.");
        }
        // Resume if same song was paused
        if (songIsPaused && song == currentSong) {
            songIsPaused = false;
            cout << "Resuming song: " << song->getTitle() << "\n";
            aod->playSound(song);
            return;
        }

        currentSong = song;
        songIsPaused = false;
        cout << "Playing song: " << song->getTitle() << "\n";
        aod->playSound(song);
    }

    void pause() {
        if (currentSong == nullptr) {
            throw runtime_error("No song is currently playing to pause.");
        }
        if (songIsPaused) {
            throw runtime_error("Song is already paused.");
        }
        songIsPaused = true;
        cout << "Pausing song: " << currentSong->getTitle() << "\n";
    }
};