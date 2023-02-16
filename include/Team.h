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
    ushort id = 0;
    const char * name;
    ushort matchesWon = 0;
    ushort matchesLost = 0;
    Player *playerFront;
    Player *playerBack;
public:
    Team(ushort id, const char * name, Player *playerFront, Player *playerBack);
    ~Team();
    ushort getId();
    const char * getName();
    ushort getMatchesWon();
    ushort getMatchesLost();
    Player *getPlayerFront();
    Player *getPlayerBack();

    void winMatch();
    void looseMatch();
};

#endif