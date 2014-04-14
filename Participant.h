#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include <string>

class Participant {
public:
    Participant(std::string name_) : name(name_), score(0), resource(1000) {}
    
    virtual ~Participant() {}
    
    void add_score(int score_) {score += score_;}
    
    virtual void init() = 0;
    
    virtual void run() = 0;
    
private:
    std::string name;
    int score;
    int resource;
};

#endif
