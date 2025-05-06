#include "../include/archerSquirrel.h"

ArcherSquirrel::ArcherSquirrel(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/archerSquirrel.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 64.0f / textureSize.x;
    float scaleY = 64.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));
    mRadius = 30;
    mPos = position;
    mFireRate = 10; //sleep 10 seconds between attacks
    //mDamage = 10; //take 1 hp from first 10 enemies
    mSprite.setPosition(mPos);
}

void ArcherSquirrel::attack(std::queue<Enemy> &q)
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