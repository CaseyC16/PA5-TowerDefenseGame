/**
 * @file pinecone.cpp
 * @author Joseph Moran
 * @brief  Implementation file for projectile class
 * @version 0.1
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
#include "../include/pinecone.h"
#include <cmath>

/**
 * @brief Construct a new Pine Cone:: Pine Cone object
 * 
 * @param startPos starting position
 * @param target Enemy
 */
PineCone::PineCone(sf::Vector2f startPos, Enemy *target)
{
    //load texture
    if(!mTexture.loadFromFile("resources/singlePineConeFinalProject.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);

    //set scale
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 20.0f / textureSize.x;
    float scaleY = 20.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));

    //set origin to center
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
    mPosition = startPos;
    mSprite.setPosition(mPosition);
    mSpeed = 200.0f;

    if(target) 
    {
        sf::Vector2f targetPos = target->getSprite().getPosition();
        sf::Vector2f dir = targetPos - startPos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        
        //normalize/scale by speed
        if(length > 0)
        {
            mVelocity = (dir / length) * mSpeed;
            
            //find rotation angle (degrees)
            float angle = std::atan2(dir.y, dir.x) * 180.f / static_cast<float>(M_PI);
            mSprite.setRotation(angle + 90.f); //adjust based on sprite orientation
        } 
        else
        {
            mVelocity = sf::Vector2f(0.f, 0.f);
        }
    }
}

/**
 * @brief update position of bullet
 * 
 * @param deltaTime 
 */
void PineCone::update(float deltaTime)
{
    //mSprite.move(mVelocity * deltaTime);

    //update position
    mPosition += mVelocity * deltaTime;
    mSprite.setPosition(mPosition);
    
    //add spin to pinecone
    mSprite.rotate(360.0f * deltaTime); // Full rotation per second
}

/**
 * @brief check if bullet hits enemy
 * 
 * @param target enemy
 * @return true 
 * @return false 
 */
bool PineCone::hasHitTarget(Enemy *target) const
{
    //check if enemy exists
    if (!target || (!target->getHealth()) > 0)
    {
        return false;
    }

    //get sprite bounds
    sf::FloatRect targetBounds = target->getSprite().getGlobalBounds();
    sf::FloatRect bulletBounds = mSprite.getGlobalBounds();

    //detect collisions
    return bulletBounds.intersects(targetBounds);
}

/**
 * @brief checks if bullet is out of range
 * 
 * @param bounds map boundary
 * @return true 
 * @return false 
 */
bool PineCone::outOfRange(const sf::FloatRect& bounds) const
{
    //return !bounds.intersects(mSprite.getGlobalBounds());

    return !bounds.contains(mPosition);
}
