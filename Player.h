#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
public:
    Player(const std::string& name_) : name(name_), score(0), resource(1000) {}
    
    virtual ~Player() {}
    
    void add_score(int score_) {score += score_;}

    virtual void init() = 0;
    
    virtual bool run() = 0;
    
private:
    std::string name;
    int score;
    int resource;
};

#endif
