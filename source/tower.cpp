#include "../include/tower.h"

void Tower::addTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy enters the radius
    mTargets.push(e);
}

void Tower::removeTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy leaves the radius
    mTargets.pop();
}

void Tower::draw(sf::RenderWindow &window)
{
    window.draw(mSprite);
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