#include "Player.h"
#include "Human_player.h"
#include "Computer_player.h"
#include "Model.h"
#include "Utility.h"
#include <iostream>
#include <iomanip>
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
using std::setw;

const int number_of_turn = 100;

int read_positive_int();
int read_non_nagetive_int();
void skip_line();

int main ()
{
	// Set output to show two decimal places
    //	cout << fixed << setprecision(2) << endl;
	cout.setf(ios::fixed, ios::floatfield);
	cout.precision(2);
    
    // ask the number of human players and computer players
    int human_players;
    int computer_players;
    while (true) {
        try {
            cout << "Please specify number of human players: ";
            human_players = read_positive_int();
            cout << "Please specify number of computer players: ";
            computer_players = read_non_nagetive_int();
            break;
        } catch (Error& e) {
            skip_line();
            cout << e.what() << endl;
        }
    }
    
    // create a container to hold all players
    map<string, shared_ptr<Player>> player_container;
    for (int i = 1; i <= human_players; ++i) {
        while (true) {
            cout << "Please specify player " << i << "'s name: ";
            string name;
            cin >> name;
            if (player_container.find(name) != player_container.end()) {
                cout << "Name already in use!" << endl;
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
    
    // initial stage
    cout << "\nInitial stage:" << endl;
    for (auto& entry : player_container) {
        cout << entry.first << ", ";
        entry.second->init();
    }
    
    // start simulating
    for (int i = 0; i < number_of_turn; ++i) {
        for (auto itr = player_container.begin(); itr != player_container.end();) {
            cout << "\nPlayer " << itr->first << "'s turn:" << endl;
            if (!itr->second->run()) {
                cout << "Human player " << itr->first << " has quited!" << endl;
                player_container.erase(itr++);
            } else {
                ++itr;
            }
        }
        if (player_container.empty()) {
            break;
        }
        cout << endl;
        Model::get_instance().update();
    }
    
    // show result
    cout << "----- Result -----" << endl;
    cout << setw(10) << "Player" << setw(10) << "Score" << endl;    
    int winner_score;
    string winner_name;    
    for (auto& entry : player_container) {
        int score = entry.second->get_score();
        if (winner_name.empty() || score > winner_score) {
            winner_score = score;
            winner_name = entry.first;
        }
        cout << setw(10) << entry.first << setw(10) << score << endl;
    }
    cout << "\nWinner is: " << winner_name << ", score: " << winner_score << endl;
    return 0;
}

int read_positive_int() {
    int i;
    if (!(cin >> i) || i <= 0) {
        throw Error("Please enter a positive integer!");
    }
    return i;
}

int read_non_nagetive_int() {
    int i;
    if (!(cin >> i) || i < 0) {
        throw Error("Please enter a non-nagetive integer!");
    }
    return i;
}

void skip_line() {
    cin.clear();
    while (cin.get() != '\n');
}
