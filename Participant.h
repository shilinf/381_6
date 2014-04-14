#ifndef PARTICIPANT_H
#define PARTICIPANT_H

class Participant {
public:
    Participant() : score(0), resource(1000) {}
    
    virtual ~Participant() {}
    
    void add_score(int score_) {score += score_;}
    
    virtual void init() = 0;
    
    virtual bool run() = 0;
    
private:
    int score;
    int resource;
};

#endif
