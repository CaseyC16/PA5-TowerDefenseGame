#include "../include/coneThrower.h"

ConeThrower::ConeThrower(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/testTree.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mRadius = 50;
    mPos = position;
    mFireRate = 5;
    mDamage = 1;
    mSprite.setPosition(mPos);
}

void ConeThrower::attack(std::queue<Enemy> &q)
{
    //take one hp from first enemy in queue
    //can call Enemy targeted function instead of manually removing health
    int health = (q.front()).getHealth();
    health--;
    if(health < 1)
    {
        q.pop(); //remove enemy from queue if destroyed
    }
    else
    {
        (q.front()).setHealth(health); //remove one hp
    }
}