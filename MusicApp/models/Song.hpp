#pragma once
#include <string>
using namespace std;


class Song {
private:
    string title;
    string artist;
    string path;
public:
    Song(string title , string artist , string path) {
        this -> title = title;
        this -> artist = artist;
        this -> path = path;
    }

    string getTitle() {
        return title;
    }

    string getArtist()  {
        return artist;
    }
    string getPath() {
        return path;
    }
};