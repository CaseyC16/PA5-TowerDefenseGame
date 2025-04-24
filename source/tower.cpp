#include "../include/tower.h"

Tower::Tower() : mRadius(0), mPos(0.f,0.f), mFireRate(0), mDamage(0)
{}

void Tower::setSprite(std::string fileName)
{
    if(!mTexture.loadFromFile(fileName))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    //create sprite that looks like a tree
    (mSprite.getSprite()).setTexture(mTexture);
}

void Tower::drawTower(sf::RenderWindow &window)
{
    window.draw(mSprite);
}

ConeThrower::ConeThrower(sf::Vector2f position)
{
    //this->setSprite("resources/testTree.png");
    mSprite = TestSprite("resources/testTree.png", position, sf::Vector2f(100.f,100.f));
    mRadius = 50;
    mPos = position;
    mFireRate = 5;
    mDamage = 1;
}

void ConeThrower::attack(std::queue<Enemy> &q)
{
    //q.setHealth(1);
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