#include "database.h"

Database::Database()
:song_list(), init(true)
{ }

// boolean operators to compare song features (used for sort method)
bool operator<(Song song1, Song song2) {
    if (song1.get_name() < song2.get_name()) {
        return true;
    }
    else {
        return false;
    }
}

bool compare_durations(Song song1, Song song2) {
    if (song1.get_duration() < song2.get_duration()) {
        return true;
    }
    else {
        return false;
    }
}

bool compare_dates(Song song1, Song song2) {
    if (song1.get_year() < song2.get_year()) {
        return true;
    }
    else {
        return false;
    }
}

bool compare_artists(Song song1, Song song2) {
    if (song1.get_artist() < song2.get_artist()) {
        return true;
    }
    else {
        return false;
    }
}

vector<Song> Database::find_singles_only() {
    vector<Song> songs;
    for (int i = 0; i < song_list.size(); i++) {
        if (song_list[i].is_single()) {
            songs.push_back(song_list[i]);
        }
    }

    if (songs.size() == 0) {
        cout << "No matching songs.\n";
    }

    return songs;
}

vector<Song> Database::find_album_only() {
    vector<Song> songs;
    for (int i = 0; i < song_list.size(); i++) {
        if (!(song_list[i].is_single())) {
            songs.push_back(song_list[i]);
        }
    }

    if (songs.size() == 0) {
        cout << "No matching songs.\n";
    }

    return songs;
}

vector<Song> Database::find_by_name(string name, bool reversed) {
    if (name != "") {
        vector<Song> songs;
        for (int i = 0; i < song_list.size(); i++) {
            if ((song_list[i].get_name() == name) || 
            (song_list[i].get_name().find(name) != string::npos)) {
                songs.push_back(song_list[i]);
            }
        }

        if (songs.size() == 0) {
            cout << "No matching songs.\n";
            return songs;
        }

        sort(songs.begin(), songs.end());

        if (!reversed) {
            reverse(songs.begin(), songs.end());
        }
        return songs;
    }
    else {
        sort(song_list.begin(), song_list.end());
        if (reversed) {
            reverse(song_list.begin(), song_list.end());
        }
        return song_list;
    }
}

// Finds songs that have a specific duration
vector<Song> Database::find_precise_duration(int duration) {
    vector<Song> songs;
    for (int i = 0; i < song_list.size(); i++) {
        if (song_list[i].get_duration() == duration) {
            songs.push_back(song_list[i]);
        }
    }

    if (songs.size() == 0) {
        cout << "No matching songs.\n";
    }

    return songs;
}

// Finds all songs that have a duration within begin and end, and can order them in descending
// and ascending order
vector<Song> Database::find_range_duration(int begin, int end, bool desc) {
    if (begin != 0 && end != 0) {
        vector<Song> songs;
        for (int i = 0; i < song_list.size(); i++) {
            if ((song_list[i].get_duration() >= begin) && (song_list[i].get_duration() <= end)) {
                songs.push_back(song_list[i]);
            }
        }

        if (songs.size() == 0) {
            cout << "No matching songs.\n";
            return songs;
        }

        sort(songs.begin(), songs.end(), compare_durations);

        if (desc) {
            reverse(songs.begin(), songs.end());
        }
        return songs;
    }
    else {
        sort(song_list.begin(), song_list.end(), compare_durations);
        if (desc) {
            reverse(song_list.begin(), song_list.end());
        }
        return song_list;
    }
}

// Finds a specific year that a song was released
vector<Song> Database::find_precise_year(int year) {
    vector<Song> songs;
    for (int i = 0; i < song_list.size(); i++) {
        if (song_list[i].get_year() == year) {
            songs.push_back(song_list[i]);
        }
    }

    if (songs.size() == 0) {
        cout << "No matching songs.\n";
    }

    return songs;
}

// Allows for a range of years to be found and can order them in ascending and descending order
vector<Song> Database::find_range_year(int begin, int end, bool desc) {
    if (begin != 0 && end != 0) {
        vector<Song> songs;
        for (int i = 0; i < song_list.size(); i++) {
            if ((song_list[i].get_year() >= begin) && (song_list[i].get_year() <= end)) {
                songs.push_back(song_list[i]);
            }
        }

        if (songs.size() == 0) {
            cout << "No matching songs.\n";
            return songs;
        }

        sort(songs.begin(), songs.end(), compare_dates);

        if (desc) {
            reverse(songs.begin(), songs.end());
        }

        return songs;
    }
    else {
        sort(song_list.begin(), song_list.end(), compare_dates);
        if (desc) {
            reverse(song_list.begin(), song_list.end());
        }
        return song_list;
    }
}

vector<Song> Database::find_by_artist(string artist, bool reversed) {
    if (artist != "") {
        vector<Song> songs;
        for (int i = 0; i < song_list.size(); i++) {
            if (song_list[i].get_artist() == artist || 
            (song_list[i].get_artist().find(artist) != string::npos)) {
                songs.push_back(song_list[i]);
            }
        }

        if (songs.size() == 0) {
            cout << "No matching songs.\n";
            return songs;
        }
        sort(songs.begin(), songs.end(), compare_artists);

        if (reversed) {
            reverse(songs.begin(), songs.end());
        }
        return songs;
    }
    else {
        sort(song_list.begin(), song_list.end(), compare_artists);
        if (reversed) {
            reverse(song_list.begin(), song_list.end());
        }
        return song_list;
    }

}

// Checks if a song is already in the database
bool Database::does_exist(string name, string artist) {
    if(song_list.size() == 1 || song_list.size() == 0) {
        return false;
    }
    else {
        for (int i = 0; i < song_list.size(); i++) {
            if (song_list[i].get_name() == name && song_list[i].get_artist() == artist) {
                return true;
            }
        }
    }
    return false;
}

void Database::add_song(string name, string artist, int duration, int year, bool single) {
    Song new_song;
    new_song.set_name(name);
    new_song.set_artist(artist);
    new_song.set_duration(duration);
    new_song.set_release(year);
    new_song.set_single(single);

    song_list.push_back(new_song);
}

bool Database::delete_song(string name, string artist) {
    for (int i = 0; i < song_list.size(); i++) {
        if (song_list[i].get_name() == name && song_list[i].get_artist() == artist) {
            song_list.erase(song_list.begin() + i);
            return true;;
        }
    }

    return false;
}

// Read in songs
// Formatted by: [Song Name][Artist][Duration][Release Year][Single]
void Database::start() {
    if (init) {
        ifstream infile("database.txt");
        string word;

        while(getline(infile, word)) {
            Song new_song;
            string name = word.substr(word.find('[') + 1, word.find(']') - word.find('[') - 1);

            new_song.set_name(name);

            word = word.substr(word.find(']') + 1);

            string artist = word.substr(word.find('[') + 1, word.find(']') - word.find('[') - 1);

            new_song.set_artist(artist);

            word = word.substr(word.find(']') + 1);

            string duration = word.substr(word.find('[') + 1, word.find(']') - word.find('[') - 1);

            new_song.set_duration(stoi(duration));

            word = word.substr(word.find(']') + 1);

            string year = word.substr(word.find('[') + 1, word.find(']') - word.find('[') - 1);

            new_song.set_release(stoi(year));

            word = word.substr(word.find(']') + 1);

            string single = word.substr(word.find('[') + 1, word.find(']') - word.find('[') - 1);

            if (single == "y") {
                new_song.set_single(true);
            }
            else {
                new_song.set_single(false);
            }

            song_list.push_back(new_song);
        }
    }
}

// Write updated information to the file.
void Database::end() {
    ofstream outfile("database.txt");
    if (outfile.is_open()) {
        for (int i = 0; i < song_list.size(); i++) {
            outfile << "[" << song_list[i].get_name() << "]";
            outfile << "[" << song_list[i].get_artist() << "]";
            outfile << "[" << song_list[i].get_duration() << "]";
            outfile << "[" << song_list[i].get_year() << "]";

            if (song_list[i].is_single()) {
                outfile << "[y]\n";
            }
            else {
                outfile << "[n]\n";
            }
        }
        outfile.close();
    }
}

bool Database::is_init() {
    return init;
}

void Database::set_init(bool ans) {
    init = ans;
}