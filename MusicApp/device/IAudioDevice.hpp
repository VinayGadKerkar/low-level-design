#pragma once 
#include <string>
#include "../models/Song.hpp"

class IAudioDevice {
    public:
        virtual void playSound(Song *song) = 0;
        virtual ~IAudioDevice() = default;
};