#include "Team.h"

Team::Team(ushort id, const char * name, Player *playerFront, Player *playerBack)
{
    this->id = id;
    this->name = name;
    this->playerFront = playerFront;
    this->playerBack = playerBack;
}

Team::~Team()
{
}


ushort Team::getId()
{
    return id;
}

const char * Team::getName()
{
    return name;
}

Player *Team::getPlayerFront()
{
    return playerFront;
}

Player *Team::getPlayerBack()
{
    return playerBack;
}

ushort Team::getMatchesWon()
{
    return matchesWon;
}

ushort Team::getMatchesLost()
{
    return matchesLost;
}

void Team::winMatch()
{
    matchesWon++;
    playerFront->winMatch();
    playerBack->winMatch();
    
}

void Team::looseMatch()
{
    matchesLost++;
    
    playerFront->looseMatch();
    playerBack->looseMatch();
}