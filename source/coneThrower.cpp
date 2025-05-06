#include "../include/coneThrower.h"

ConeThrower::ConeThrower(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/coneSquirrel.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 64.0f / textureSize.x;
    float scaleY = 64.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));
    mRadius = 50;
    mPos = position;
    mFireRate = 1; //sleep one second between attacks
    //mDamage = 1; //take one hp from enemy
    mSprite.setPosition(mPos);
}

void ConeThrower::attack(std::queue<Enemy> &q)
{
    //take one hp from first enemy in queue
    //can call Enemy targeted function instead of manually removing health
    Enemy temp = q.front();
    // int health = temp.getHealth();
    q.pop(); //remove enemy from queue
    temp.targeted(); //shoot at enemy
}