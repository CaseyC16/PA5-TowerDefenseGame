#include "../include/enemyclass.h"
#include <iostream>

//when you want to create a new enemy use code below
//Enemy * enemy = new Enemy(peasant or knight or heavyKnight);

Enemy::Enemy(enemyType type) : mType(type)
{
    setType(type);
}

//sets the type of enemy based on what enum is passed to it
void Enemy::setType(enemyType newType)
{
    mType = newType;

    if(mType == peasant)
    {
        setHealth(1);
        setSpeed(1);
        setSprite("resources/enemy_farmer.png");
    }
    if(mType == knight)
    {
        setHealth(2);
        setSpeed(2);
        setSprite("resources/enemy_armor.png");
    }
    if(mType == heavyKnight)
    {
        setHealth(3);
        setSpeed(3);
        setSprite("resources/enemy_heavyarmor.png");
    }
}

void Enemy::setHealth(int newhealth)
{
    if(newhealth >= 0)
    {
        mHealth = newhealth;
    }
}

void Enemy::setSpeed(int newspeed)
{
    mSpeed = newspeed;
}

void Enemy::setSprite(const std::string & sprite)
{
    if (!mTexture.loadFromFile(sprite))
    {
        exit(TEXTURE_LOADING_ERROR);
    }
    mSprite.setTexture(mTexture);
}

void Enemy::drawSprite(sf::RenderWindow & window)
{
    window.draw(mSprite);
}

void Enemy::targeted() 
{
    // Reduce health
    setHealth(getHealth() - 1);

    // changing enemy type
    if (getHealth() == 2 && mType == heavyKnight)
    {
        setType(knight);
    }
    else if (getHealth() == 1 && mType == knight)
    {
        setType(peasant);
    }
    else if (getHealth() <= 0)
    {
        delete this;
    }
}

Enemy::~Enemy()
{
    //rewarded with nuts when enemy is defeated
    // amount TBD
    //nuts++
}