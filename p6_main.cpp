#include "Player.h"
#include "Human_player.h"
#include "Computer_player.h"
#include "Utility.h"
#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <memory>

using std::ios;
using std::cin; using std::cout; using std::endl;
using std::string; using std::to_string;
using std::map;
using std::mem_fn;
using std::shared_ptr;

int read_positive_int();
void skip_line();

int main ()
{
	// Set output to show two decimal places
    //	cout << fixed << setprecision(2) << endl;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
    
    // ask the number of human players and bots
    int human_players;
    int computer_players;
    while (true) {
        try {
            cout << "Please specify number of human players: ";
            human_players = read_positive_int();
            cout << "Please specify number of bots: ";
            computer_players = read_positive_int();
            break;
        } catch (Error& e) {
            cout << e.what() << endl;
        }
    }
    
    // create a container to hold all participants
    map<string, shared_ptr<Player>> player_container;
    for (int i = 1; i <= human_players; ++i) {
        while (true) {
            cout << "Please specify player " << i << "'s name: ";
            string name;
            cin >> name;
            if (player_container.find(name) != player_container.end()) {
                cout << "Name Already in use!" << endl;
                continue;
            }
            player_container[name] = shared_ptr<Player>(new Human_player(name));
            break;
        }
    }
    for (int i = 0; i < computer_players; ++i) {
        string name = "Computer player " + to_string(i);
        player_container[name] = shared_ptr<Player>(new Computer_player(name));
    }
    
    // init 
    for (auto& entry : player_container) {
        entry.second->init();
    }
    
    // start simulating
    int turns = 5;
    for (int i = 0; i < turns; ++i) {
        cout << "\nTurn " << i << ":" << endl;
        for (auto itr = player_container.begin(); itr != player_container.end();) {
            cout << "\nPlayer " << itr->first << "'s turn:" << endl;
            if (!itr->second->run()) {
                cout << "Human player " << itr->first << " has quited!" << endl;
                player_container.erase(itr++);
            } else {
                ++itr;
            }
        }
    }
    
    return 0;
}

int read_positive_int() {
    int positive_int;
    if (!(cin >> positive_int) || positive_int <= 0) {
        skip_line();
        throw Error("Please enter a positive integer!");
    }
    return positive_int;
}

void skip_line() {
    cin.clear();
    while (cin.get() != '\n');
}
