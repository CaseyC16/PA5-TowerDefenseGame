#include "../include/pinecone.h"
#include <cmath>

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

        // sf::Vector2f dir = (target->getSprite()).getOrigin() - startPos;
        // float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        // mVelocity = (length != 0) ? (dir / length) * mSpeed : sf::Vector2f(0.f, 0.f);
    }
}

void PineCone::update(float deltaTime)
{
    //mSprite.move(mVelocity * deltaTime);

    //update position
    mPosition += mVelocity * deltaTime;
    mSprite.setPosition(mPosition);
    
    //add spin to pinecone
    mSprite.rotate(360.0f * deltaTime); // Full rotation per second
}

bool PineCone::hasHitTarget(Enemy *target) const
{
    //check if enemy exists
    if (!target) return false;
    
    //detect collisions
    return mSprite.getGlobalBounds().intersects(target->getSprite().getGlobalBounds());
}

bool PineCone::outOfRange(const sf::FloatRect& bounds) const
{
    //return !bounds.intersects(mSprite.getGlobalBounds());

    return !bounds.contains(mPosition);
}
