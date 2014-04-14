#ifndef COMPUTER_PLAYER_H
#define COMPUTER_PLAYER_H

#include "Player.h"

class Computer_player : public Player {
public:
    Computer_player(const std::string& name_) : Player(name_) {}
    
    void init() override;

    bool run() override;
    
private:
};

#endif
