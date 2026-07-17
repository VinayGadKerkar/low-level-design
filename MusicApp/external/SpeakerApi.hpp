#pragma once
#include<string>
#include<iostream>

using namespace std;

class SpeakerAPI {
public:
    void playSoundViaCable(const string& data) {
        cout << "[WiredSpeaker] Playing: " << data << "\n";
        // mimics playing music
    }
};