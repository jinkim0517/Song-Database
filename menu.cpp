#include "menu.h"

// Main menu (uses ncurses)
void Menu::start_menu(Database& user_info) {
    if (user_info.is_init()) {
        user_info.start();
        user_info.set_init(false);
    }

    initscr();
    noecho();
    curs_set(0);

    int y_max = 0;
    int x_max = 0;

    getmaxyx(stdscr, y_max, x_max);

    WINDOW *menuwin = newwin(15, x_max - 12, y_max - 60, 5);
    box(menuwin, 0, 0);

    refresh();
    wrefresh(menuwin);

    keypad(menuwin, true);

    mvwprintw(menuwin, 2, 4, "Welcome to the Song Database");
    mvwprintw(menuwin, 3, 4, "----------------------------");

    mvwprintw(menuwin, 5, 4, "What would you like to do?");

    string menus[5] = {"- Add a Song", "- Delete a Song", "- Display Songs", "- Find a Song", 
    "- Quit"};

    int choice = 0;
    int highlight = 0;

    while(true) {
        for (int i = 0; i < 5; i++) {
            if (i == highlight) {
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, i + 7, 5, menus[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0) {
                    highlight = 0;
                }
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 4) {
                    highlight = 4;
                }
                break;
            default:
                break;
        }

        if (choice == 10) {
            break;
        }
    }

    switch (highlight) {
        case 0:
            endwin();
            add_menu(user_info);
            break;
        case 1:
            endwin();
            delete_menu(user_info);
            break;
        case 2:
            endwin();
            display_menu(user_info);
            break;
        case 3:
            endwin();
            find_menu(user_info);
            break;
        case 4:
            user_info.end();
            endwin();
            break;
    }
}

void Menu::add_menu(Database& user_info) {
    system("clear");

    string name;
    string artist;
    int duration;
    int year;
    char single;

    cout << "What's the name of the song?" << endl;
    getline(cin, name);

    cout << "Who made the song?" << endl;
    getline(cin, artist);

    while (user_info.does_exist(name, artist)) {
        cout << "This song has already been added! Please enter a different song.\n";
        cout << "What's the name of the song?" << endl;
        getline(cin, name);

        cout << "Who made the song?" << endl;
        getline(cin, artist);
    }

    cout << "How long is the song? (Please give in seconds)" << endl;

    while (!(cin >> duration)) {
		cout << "Please give a valid duration in seconds.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

    cout << "What year was it released?" << endl;

    while (!(cin >> year)) {
		cout << "Please give a valid year.\n";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

    cout << "Is it a single? (y/n)" << endl;

    while (!(cin >> single)) {
        cout << "Please give a valid answer.\n";
        cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (single == 'y') {
        user_info.add_song(name, artist, duration, year, true);
    }
    else if (single == 'n') {
        user_info.add_song(name, artist, duration, year, true);
    }
    else {
        while (single != 'y' && single != 'n') {
            cout << "Is it a single? (y/n)" << endl;
            cin >> single;

            if (single == 'y') {
                user_info.add_song(name, artist, duration, year, true);
            }
            else if (single == 'n') {
                user_info.add_song(name, artist, duration, year, true);
            }
        }
    }

    cout << "Song added!\n";

    char main;
    cout << "Would you like to return to the main menu? (y)\n";
    cin >> main;

    if (main == 'y' || main == 'Y') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        start_menu(user_info);
    }
    else {
        cout << "Goodbye\n";
        user_info.end();
    }
}

void Menu::delete_menu(Database& user_info) {
    system("clear");
    string name;

    cout << "What is the name of the deleted song? ";
    getline(cin, name);


    string artist;

    cout << "Who made the song? ";
    getline(cin, artist);

    if (user_info.delete_song(name, artist)) {
        cout << "Song deleted!\n";
    }
    else {
        cout << "No matching songs\n";
    }

    char main;
    cout << "Would you like to return to the main menu? (y)\n";
    cin >> main;

    if (main == 'y' || main == 'Y') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        start_menu(user_info);
    }
    else {
        cout << "Goodbye\n";
        user_info.end();
    }
}

void Menu::find_menu(Database user_info) {
    system("clear");
    cout << "How would you like to find the songs?\n";
    cout << "----------------------------------------\n" << endl;

    cout << "(A) - By Name\n";
    cout << "(B) - By Artist\n";
    cout << "(C) - By Duration\n";
    cout << "(D) - By Release Year\n";
    cout << "(E) - By Single or Album Releases?\n";
    cout << endl;
    cout << "(F) - Return to main menu\n";

    char ans;

    while (!(cin >> ans)) {
        cout << "Please choose a valid option\n";
    }

    while (ans != 'a' && ans != 'A' && ans != 'b' && ans != 'B' && ans != 'c' && ans != 'C' &&
    ans != 'd' && ans != 'D' && ans != 'e' && ans != 'E' && ans != 'f' && ans != 'F') {
        cout << "Please choose a valid option\n";
        cin >> ans;
    }

    system("clear");
    
    if (ans == 'a' || ans == 'A') {
        string name;
        cout << "Name of Song: ";
        cin.ignore();
        getline(cin, name);
        cout << endl;

        vector<Song> songs = user_info.find_by_name(name, true);
        print_songs(songs);
    }
    else if (ans == 'b' || ans == 'B') {
        string artist;
        cout << "Name of Artist: ";
        cin.ignore();

        getline(cin, artist);
        vector<Song> songs = user_info.find_by_artist(artist, true);
        print_songs(songs);
    }
    else if (ans == 'c' || ans == 'C') {
        char r_or_p;
        cout << "Would you like to search by a range or precise duration? (r/p)\n";
        cin >> r_or_p;

        while (r_or_p != 'r' && r_or_p != 'p') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid answer.\n";
            cout << "Would you like to search by a range or precise duration? (r/p)\n";
            cin >> r_or_p;
        }

        if (r_or_p == 'p') {
            int duration;
            cout << "Song Duration: ";
            
            while (!(cin >> duration)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "\nPlease enter a valid value.\n";
            }

            cout << endl;
            vector<Song> songs = user_info.find_precise_duration(duration);
            print_songs(songs);
        }
        else if (r_or_p == 'r') {
            int low = 0;
            int high = 0;
            cout << "Please enter the lower bound: ";
            cin >> low;
            cout << endl;

            cout << "Please enter the upper bound: ";
            cin >> high;
            cout << endl;

            vector<Song> songs = user_info.find_range_duration(low, high, true);
            print_songs(songs);
        }
    }
    else if (ans == 'd' || ans == 'D') {
        char r_or_p;
        cout << "Would you like to search by a range or precise year? (r/p)\n";
        cin >> r_or_p;

        while (r_or_p != 'r' && r_or_p != 'p') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nPlease enter a valid answer.\n";
            cout << "Would you like to search by a range or precise year? (r/p)\n";
            cin >> r_or_p;
        }

        if (r_or_p == 'p') {
            int year;
            cout << "Year of Release: ";
            
            while (!(cin >> year)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
                cout << "\nPlease enter a valid value.\n";
            }

            cout << endl;
            vector<Song> songs = user_info.find_precise_year(year);
            print_songs(songs);
        }
        else if (r_or_p == 'r') {
            int low = 0;
            int high = 0;
            cout << "Please enter the lower bound: ";
            cin >> low;
            cout << endl;

            cout << "Please enter the upper bound: ";
            cin >> high;
            cout << endl;

            vector<Song> songs = user_info.find_range_year(low, high, true);
            print_songs(songs);
        }
    }
    else if (ans == 'e' || ans == 'E') {
        char ans;
        cout << "Singles only? (y): ";
        cin >> ans;
        cout << endl;

        vector<Song> songs;

        if (ans == 'y') {
            songs = user_info.find_singles_only();
        }
        else {
            songs = user_info.find_album_only();
        }
        print_songs(songs);

    }
    else if (ans == 'f' || ans == 'F') {
        start_menu(user_info);
    }
    else {
        cout << "ERROR\n";
    }

    char main;
    cout << "Would you like to return to the main menu? (y)\n";
    cin >> main;

    if (main == 'y' || main == 'Y') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        start_menu(user_info);
    }
    else {
        cout << "Goodbye\n";
        user_info.end();
    }
}

void Menu::display_menu(Database& user_info) {
    system("clear");
    // Variable that tracks if this method will send the user to another screen.
    // Prevents printing "Would you like to return to the main menu" twice before exiting
    bool sent_to_next = false;
    cout << "How would you like to display your songs?\n";
    cout << "----------------------------------------\n" << endl;

    cout << "(A) - Alphabetically by Name\n";
    cout << "(B) - Alphabetically by Artist\n";
    cout << "(C) - Sorted by Duration\n";
    cout << "(D) - Sorted by Release Year\n";
    cout << "(E) - Singles or Albums Only\n";
    cout << endl;
    cout << "(F) - Return to main menu\n";

    char ans;

    while (!(cin >> ans)) {
        cout << "Please choose a valid option\n";
    }

    while (ans != 'a' && ans != 'A' && ans != 'b' && ans != 'B' && ans != 'c' && ans != 'C' &&
    ans != 'd' && ans != 'D' && ans != 'e' && ans != 'E' && ans != 'f' && ans != 'F') {
        cout << "Please choose a valid option\n";
        cin >> ans;
    }

    system("clear");
    
    if (ans == 'a' || ans == 'A') {
        vector<Song> songs;

        songs = user_info.find_by_name("", false);

        
        print_songs(songs);

        if (songs.size() == 0) {
            cout << "There are no songs in the database!\n";
        }

        char reverse;
        cout << "Press 'r' to reverse the order, or 'y' to return to main menu! ";
        cin >> reverse;

        while (reverse != 'r' && reverse != 'y') {
            cout << "Please enter a valid answer.\n";
            cin >> reverse;
        }

        if (reverse == 'r') {
            songs = user_info.find_by_name("", true);
            print_songs(songs);
        }
        else if (reverse == 'y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sent_to_next = true;
            start_menu(user_info);
        }
    }
    else if (ans == 'b' || ans == 'B') {
        vector<Song> songs;

        songs = user_info.find_by_artist("", false);

        
        print_songs(songs);

        char reverse;
        cout << "Press 'r' to reverse the order, or 'y' to return to main menu! ";
        cin >> reverse;

        while (reverse != 'r' && reverse != 'y') {
            cout << "Please enter a valid answer.\n";
            cin >> reverse;
        }

        if (reverse == 'r') {
            system("clear");
            songs = user_info.find_by_artist("", true);
            print_songs(songs);
        }
        else if (reverse == 'y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sent_to_next = true;
            start_menu(user_info);
        }
    }
    else if (ans == 'c' || ans == 'C') {
        vector<Song> songs;

        songs = user_info.find_range_duration(0, 0, false);

        print_songs(songs);

        char reverse;
        cout << "Press 'r' to reverse the order, or 'y' to return to main menu! ";
        cin >> reverse;

        while (reverse != 'r' && reverse != 'y') {
            cout << "Please enter a valid answer.\n";
            cin >> reverse;
        }
        
        if (reverse == 'r') {
            songs = user_info.find_range_duration(0, 0, true);
            print_songs(songs);
        }
        else if (reverse == 'y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sent_to_next = true;
            start_menu(user_info);
        }
        else {
            print_songs(songs);
        }
    }
    else if (ans == 'd' || ans == 'D') {
        vector<Song> songs;

        songs = user_info.find_range_year(0, 0, false);

        print_songs(songs);

        char reverse;
        cout << "Press 'r' to reverse the order, or 'y' to return to main menu! ";
        cin >> reverse;

        while (reverse != 'r' && reverse != 'y') {
            cout << "Please enter a valid answer.\n";
            cin >> reverse;
        }

        if (reverse == 'r') {
            songs = user_info.find_range_year(0, 0, true);
            print_songs(songs);
        }
        else if (reverse == 'y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sent_to_next = true;
            start_menu(user_info);
        }
    
    }
    else if (ans == 'e' || ans == 'E') {
        vector<Song> songs;

        songs = user_info.find_singles_only();

        print_songs(songs);

        char ans;
        cout << "Press 'r' to show only album releases, or 'y' to return to main menu! ";
        cin >> ans;
        cout << endl;

        while (ans != 'r' && ans != 'y') {
            cout << "Please enter a valid answer.\n";
            cin >> ans;
        }
        
        if (ans == 'r') {
            songs = user_info.find_album_only();
            print_songs(songs);
        }
        else if (ans == 'y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            sent_to_next = true;
            start_menu(user_info);
        }
    }
    else if (ans == 'f' || ans == 'F') {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        start_menu(user_info);
    }
    else {
        cout << "ERROR\n";
    }

    if (!sent_to_next) {
        char main;
        cout << "Would you like to return to the main menu? (y)\n";
        cin >> main;

        if (main == 'y' || main == 'Y') {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            start_menu(user_info);
        }
        else {
            cout << "Goodbye\n";
            user_info.end();
        }
    }
}

// Prints all songs within a given vector
void Menu::print_songs(vector<Song>& user_songs) {
    if (user_songs.size() != 0) {
        for (int i = 0; i < user_songs.size(); i++) {
            cout << "\"" << user_songs[i].get_name() << "\"" << ", by " 
            << user_songs[i].get_artist() << ", " << user_songs[i].get_duration() << " seconds, " 
            << user_songs[i].get_year() << ", ";

            if (user_songs[i].is_single()) {
                cout << "Single Release.\n";
                cout << endl;
            }
            else {
                cout << "Album Release.\n";
                cout << endl;
            }
        }
        cout << "------------------------------------------\n";
    }
}