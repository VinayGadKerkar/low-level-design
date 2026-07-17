#pragma once 
#include <string> 
#include <vector>
#include <iostream>
#include "Song.hpp"
using namespace std;

class Playlist {
    private:
        string name;
        vector<Song*> songs;
    public:
        Playlist(string name) {
            this -> name = name;
        }

        string getPlaylistName() {
            return name;
        }

        const vector<Song*>& getSongs() {
            return songs;
        }

        int getSongCount() {
            return songs.size();
        }

        void addSong(Song* song) {
            if(!song) {
                cout << "Invalid song. Cannot add to playlist." << endl;
                return;
            }
            songs.push_back(song);
        }
};