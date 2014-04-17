#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

/* The Computer player class has a simple strategy. At time 0, it creates one 
Tanker, which travels between the first and second islands, and one Cruise ship,
starting cruise from the third islands.
*/

#include "Player.h"
#include <string>

class Computer_player : public Player {
public:
    Computer_player(const std::string& name_) : Player(name_) {}
    
    void init() override;

    bool run() override;
    
private:
    std::string random_string_gen();
};

#endif
