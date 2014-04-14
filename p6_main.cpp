#include "Controller.h"
#include "Participant.h"
#include "Bot.h"
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
    int players;
    int bots;
    while (true) {
        try {
            cout << "Please specify number of human players: ";
            players = read_positive_int();
            cout << "Please specify number of bots: ";
            bots = read_positive_int();
            break;
        } catch (Error& e) {
            cout << e.what() << endl;
        }
    }
    
    // create a container to hold all participants
    map<string, shared_ptr<Participant>> participant_container;
    for (int i = 1; i <= players; ++i) {
        while (true) {
            cout << "Please specify player " << i << "'s name: ";
            string player_name;
            cin >> player_name;
            if (participant_container.find(player_name) != participant_container.end()) {
                cout << "Name Already in use!" << endl;
                continue;
            }
            participant_container[player_name] = shared_ptr<Participant>(new Controller(player_name));
            break;
        }
    }
    for (int i = 0; i < bots; ++i) {
        string bot_name = "Bot " +  to_string(i);
        participant_container[bot_name] = shared_ptr<Participant>(new Bot(bot_name));
    }
    
    // init 
    for_each(participant_container.begin(), participant_container.end(), 
        mem_fn(&Participant::init));
    
    // start simulating
    int turns = 5;
    for (int i = 0; i < turns; ++i) {
        for (auto itr = participant_container.begin(); itr != participant_container.end();) {
            if (!(itr->second->run()) {
                participant_container.erase(itr++);
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
