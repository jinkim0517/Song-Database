#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


class Song {
private:
    string name;
    string artist;
    int release_year;
    int duration;
    bool single;

public:
    Song();
    
    void set_name(string s);

    void set_artist(string s);

    void set_release(int year);

    void set_duration(int seconds);

    void set_single(bool ans);

    string get_name();

    string get_artist();

    int get_year();

    int get_duration();

    bool is_single();
};
#endif