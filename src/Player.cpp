#include "Player.h"


Player::Player(unsigned short id, const char * name)
{
    this->id = id;
    this->name = name;
}

Player::~Player()
{
    
}

unsigned short Player::getId()
{
    return id;
}

const char * Player::getName()
{
    return name;
}

unsigned short Player::getMatchesWon()
{
    return matchesWon;
}

unsigned short Player::getMatchesLost()
{
    return matchesLost;
}

void Player::winMatch()
{
    matchesWon++;
}

void Player::looseMatch()
{
    matchesLost++;
}

