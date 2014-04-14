#include "Controller.h"
#include "Participant.h"
#include "Bot.h"
#include "Utility.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>

using std::ios;
using std::cin; using std::cout; using std::endl;
using std::vector;
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
    vector<shared_ptr<Participant>> participant_container;
    for (int i = 0; i < players; ++i) {
        participant_container.push_back(shared_ptr<Participant>(new Controller));
    }
    for (int i = 0; i < bots; ++i) {
        participant_container.push_back(shared_ptr<Participant>(new Bot));
    }
    
    // init 
    for_each(participant_container.begin(), participant_container.end(), 
        mem_fn(&Participant::init));
    
    // start simulating
    int turns = 3;    
    for (int i = 0; i < turns; ++i) {
        for_each(participant_container.begin(), participant_container.end(), 
            mem_fn(&Participant::run));
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
