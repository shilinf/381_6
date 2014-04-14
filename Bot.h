#ifndef BOT_H
#define BOT_H

#include "Participant.h"

class Bot : public Participant {
public:
    void init() override;

    bool run() override;
    
private:
};

#endif
