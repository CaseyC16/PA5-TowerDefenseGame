/**
 * @file enemyClass.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for enemyClass.h
 * @date 2025-04-09
 */

#include "../include/enemyclass.h"
#include <iostream>

/**
 * @brief Constructor for Enemy object
 * 
 * @param type type is an enum that is used to decide what enemy is spawned
 */

Enemy::Enemy(enemyType type) : mType(type)
{
    setType(type);
}

/**
 * @brief this function sets all the stats to what they need to be based on the enum
 * 
 * @param newType type is an enum that is used to decide what enemy is spawned
 */
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

/**
 * @brief sets health for enemy
 * 
 * @param newhealth sent in from the setType function
 */
void Enemy::setHealth(int newhealth)
{
    if(newhealth >= 0)
    {
        mHealth = newhealth;
    }
}

/**
 * @brief sets speed for enemy
 * 
 * @param newspeed sent in from the setType function
 */
void Enemy::setSpeed(float newspeed)
{
    mSpeed = newspeed;
}

/**
 * @brief sets the sprite
 * 
 * @param sprite sent in from the setType function
 */
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

/**
 * @brief draws the sprite
 * 
 * @param window is the window of the game
 */
void Enemy::drawSprite(sf::RenderWindow & window)
{
    window.draw(mSprite);
}

/**
 * @brief when an enemy is hit with an attack either
 *        take a health away and degrade the enemy,
 *        or 
 *        delete the instance of the enemy when it reaches 0
 */
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

/**
 * @brief sets the waypoint
 * 
 * @param waypoint called from main
 */
void Enemy::setCurrentWaypoint(int waypoint)
{
    mCurrentWaypoint = waypoint;
}

/**
 * @brief updates the movement of the enemy when it reaches the next waypoint
 * 
 * @param waypoints uses the next waypoint to determine if it is close enough or not
 * @param deltaTime is used to scale the speed of the enemy
 */
void Enemy::updateMovement(const std::vector<sf::Vector2f>& waypoints, float deltaTime)
{
    //if the current waypoint is not the end waypoint
    if (mCurrentWaypoint < static_cast<int>(waypoints.size()))
    {
        // setting the base movement speed of the enemies
        float baseSpeed = 60.0f;

        //calculate the distance between the position of the sprite and the next waypoint
        sf::Vector2f target = waypoints[mCurrentWaypoint];
        sf::Vector2f currentPos = mSprite.getPosition();
        sf::Vector2f direction = target - currentPos;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        
        //calculates the total movement speed of the enemy based on their base speed, the enemyType speed and the last rendered frame
        //deltatime makes the speed reliant on real time instead of dependent on machine time, makes the speed constant on all computers
        float movement = baseSpeed * getSpeed() * deltaTime;

        // if the distance left to the next waypoint is greater that the movement of the enemy
        if (distance > movement) 
        {
            // normalize the direction so that movement is fluid and then move the sprite
            direction /= distance; 
            mSprite.move(direction * movement);
        }
        // means that the enemy is close enough to the waypoint to start to head to the next waypoint
        else 
        {   
            // sets the position of the enemy on the target, and tells the enemy that its time to move onto the next waypoint
            mSprite.setPosition(target);
            mCurrentWaypoint++;
        }
    }
}
