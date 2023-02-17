#ifndef __TEAM_H
#define __TEAM_H

#if (ARDUINO >= 100)
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "Player.h"

class Team
{
private:
    unsigned short id = 0;
    const char * name;
    unsigned short matchesWon = 0;
    unsigned short matchesLost = 0;
    Player *playerFront;
    Player *playerBack;
public:
    Team(unsigned short id, const char * name, Player *playerFront, Player *playerBack);
    ~Team();
    unsigned short getId();
    const char * getName();
    unsigned short getMatchesWon();
    unsigned short getMatchesLost();
    Player *getPlayerFront();
    Player *getPlayerBack();

    void winMatch();
    void looseMatch();
};

#endif