#include "../include/branchSpike.h"

BranchSpike::BranchSpike(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/testTree.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    mRadius = 30;
    mPos = position;
    mFireRate = 10; //sleep 10 seconds between attacks
    //mDamage = 10; //take 1 hp from first 10 enemies
    mSprite.setPosition(mPos);
}

void BranchSpike::attack(std::queue<Enemy> &q)
{
    //take one hp from all enemies
    while(!q.empty())
    {
        Enemy temp = q.front(); //save enemy in case it is destroyed by attack
        // int health = temp.getHealth();
        q.pop(); //remove enemy from queue
        temp.targeted(); //shoot at enemy
    }
}