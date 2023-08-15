#ifndef DATABASE_H
#define DATABASE_H

#include "songs.h"
#include "curses.h"
#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <limits>
#include <fstream>

class Database {
private:
    vector<Song> song_list;
    
    // Checks if the program has just started or if the user has returned to main menu.
    // Prevents multiple read-ins of the data file.
    bool init;
public:
    Database();

    void sort_by_year(vector<Song>& songs, bool desc);

    vector<Song> find_singles_only();

    vector<Song> find_album_only();

    vector<Song> find_by_name(string name, bool reversed);

    vector<Song> find_precise_duration(int duration);

    vector<Song> find_range_duration(int begin, int end, bool desc);

    vector<Song> find_precise_year(int year);

    vector<Song> find_range_year(int begin, int end, bool desc);

    vector<Song> find_by_artist(string artist, bool reversed);

    bool does_exist(string name, string artist);

    void add_song(string name, string artist, int duration, int year, bool single);
    
    bool delete_song(string name, string artist);

    void start();

    void end();

    void get_size();

    bool is_init();

    void set_init(bool ans);
};

#endif