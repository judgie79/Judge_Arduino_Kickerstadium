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
    ushort id = 0;
    const char * name;
    ushort matchesWon = 0;
    ushort matchesLost = 0;
public:
    Player(ushort id, const char * name);
    ~Player();
    ushort getId();
    const char * getName();
    ushort getMatchesWon();
    ushort getMatchesLost();

    void winMatch();
    void looseMatch();
};

#endif