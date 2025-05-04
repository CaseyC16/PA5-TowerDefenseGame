#include "../include/assaultSquirrel.h"

AssaultSquirrel::AssaultSquirrel(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/assaultSquirrel.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 64.0f / textureSize.x;
    float scaleY = 64.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));
    // mSprite.setScale(sf::Vector2f(0.1f,0.1f));
    mRadius = 25;
    mPos = position;
    mFireRate = 15; //sleep 15 seconds between attacks
    //mDamage = 10; //destroy all enemies in range
    mSprite.setPosition(mPos);
}

void AssaultSquirrel::attack(std::queue<Enemy> &q)
{
    //destroy all enemies in range
    while(!q.empty())
    {
        Enemy temp = q.front();
        int health = temp.getHealth();
        if(health < 2)
        {
            q.pop(); //only remove enemy from queue if it's about to be destroyed
        }
        //shoot at enemy
        temp.targeted();
    }
}