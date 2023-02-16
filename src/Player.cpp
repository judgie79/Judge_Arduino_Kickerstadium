#include "Player.h"


Player::Player(ushort id, const char * name)
{
    this->id = id;
    this->name = name;
}

Player::~Player()
{
    
}

ushort Player::getId()
{
    return id;
}

const char * Player::getName()
{
    return name;
}

ushort Player::getMatchesWon()
{
    return matchesWon;
}

ushort Player::getMatchesLost()
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

