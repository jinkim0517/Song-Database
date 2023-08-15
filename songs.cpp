#include "songs.h"

using namespace std;

Song::Song() 
:name(), artist(), release_year(0), duration(0), single(false)
{ }

void Song::set_name(string s) {
    name = s;
}

void Song::set_artist(string s) {
    artist = s;
}

void Song::set_release(int year) {
    release_year = year;
}

void Song::set_duration(int seconds) {
    duration = seconds;
}

void Song::set_single(bool ans) {
    single = ans;
}

string Song::get_name() {
    return name;
}

string Song::get_artist() {
    return artist;
}

int Song::get_year() {
    return release_year;
}

int Song::get_duration() {
    return duration;
}

bool Song::is_single() {
    return single;
}