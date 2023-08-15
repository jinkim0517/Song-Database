#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include "songs.h"
#include "database.h"
#include <curses.h>

class Menu {
public:
    void start_menu(Database& user_info);

    void add_menu(Database& user_info);

    void delete_menu(Database& user_info);

    void display_menu(Database& user_info);

    void find_menu(Database user_info);

    void print_songs(vector<Song>& user_songs);
};

#endif