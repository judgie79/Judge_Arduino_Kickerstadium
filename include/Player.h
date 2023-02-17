#ifndef __PLAYER_H
#define __PLAYER_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Player
{
private:
    unsigned short id = 0;
    const char * name;
    unsigned short matchesWon = 0;
    unsigned short matchesLost = 0;
public:
    Player(unsigned short id, const char * name);
    ~Player();
    unsigned short getId();
    const char * getName();
    unsigned short getMatchesWon();
    unsigned short getMatchesLost();

    void winMatch();
    void looseMatch();
};

#endif