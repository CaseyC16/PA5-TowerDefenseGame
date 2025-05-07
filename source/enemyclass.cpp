/**
 * @file enemyClass.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for enemyClass.h
 * @date 2025-04-09
 */

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
        setSpeed(1.0f);
        setSprite("resources/enemy_farmer.png");
    }
    if(mType == knight)
    {
        setHealth(2);
        setSpeed(1.25f);
        setSprite("resources/enemy_armor.png");
    }
    if(mType == heavyKnight)
    {
        setHealth(3);
        setSpeed(1.5f);
        setSprite("resources/enemy_heavyarmor.png");
    }
}

//sets health for enemy
void Enemy::setHealth(int newhealth)
{
    if(newhealth >= 0)
    {
        mHealth = newhealth;
    }
}

//sets speed for enemy
void Enemy::setSpeed(float newspeed)
{
    mSpeed = newspeed;
}

//sets the sprite
void Enemy::setSprite(const std::string & sprite)
{
    if (!mTexture.loadFromFile(sprite))
    {
        exit(TEXTURE_LOADING_ERROR);
    }
    mSprite.setTexture(mTexture);

    //resize the sprite
    mSprite.setScale(0.3f, 0.3f);

    //setting the origin of the sprite to be at the bottom middle of the image
    sf::Vector2u textureSize = mTexture.getSize();
    mSprite.setOrigin(textureSize.x / 3.5f, textureSize.y);
}

//draws the sprite
void Enemy::drawSprite(sf::RenderWindow & window)
{
    window.draw(mSprite);
}

//when an enemy is hit with an attack delete the instance of the enemy and make and enemy with a lower class
void Enemy::targeted() 
{
    // reduce health
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

void Enemy::setCurrentWaypoint(int waypoint)
{
    mCurrentWaypoint = waypoint;
}

void Enemy::updateMovement(const std::vector<sf::Vector2f>& waypoints, float deltaTime)
{
    if (mCurrentWaypoint < static_cast<int>(waypoints.size()))
    {
        sf::Vector2f target = waypoints[mCurrentWaypoint];
        sf::Vector2f currentPos = mSprite.getPosition();
        sf::Vector2f direction = target - currentPos;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Base movement speed (pixels per second)
        float baseSpeed = 60.0f;
        
        // Scale by enemy-specific speed modifier and deltaTime
        float movement = baseSpeed * getSpeed() * deltaTime;

        // If the enemy is not close enough to the waypoint
        if (distance > movement) 
        {
            // Normalize direction
            direction /= distance; 
            mSprite.move(direction * movement);
        }
        // If the enemy is close enough to the waypoint move on to the next waypoint
        else 
        {   
            // Move exactly to the waypoint
            mSprite.setPosition(target);
            mCurrentWaypoint++;
        }
    }
}


Enemy::~Enemy()
{

}