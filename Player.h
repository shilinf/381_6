#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <memory>

class Player : public std::enable_shared_from_this<Player> {
public:
    Player(const std::string& name_) : name(name_), score(0), resource(1000) {}
    
    virtual ~Player() {}
    
    void add_score(int score_) {score += score_;}
    
    int get_score() {return score;}
    
    void use_resource(int resource);
    
    const std::string& get_name() const {return name;}
    
    virtual void init() = 0;
    
    virtual bool run() = 0;
    
private:
    std::string name;
    int score;
    int resource;
};

#endif
