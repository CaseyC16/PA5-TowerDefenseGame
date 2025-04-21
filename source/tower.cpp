#include "../include/tower.h"

Tower::Tower() : mRadius(0), mPos(0.f,0.f), mFireRate(0), mDamage(0)
{}

ConeThrower::ConeThrower(sf::Vector2f position)
{
    mRadius = 50;
    mPos = position;
    mFireRate = 5;
    mDamage = 1;
}

BranchSpike::BranchSpike(sf::Vector2f position)
{
    mRadius = 25;
    mPos = position;
    mFireRate = 2;
    mDamage = 1;
}

ConeBomb::ConeBomb(sf::Vector2f position)
{
    mRadius = 35;
    mPos = position;
    mFireRate = 3;
    mDamage = 3;
}