#include "../include/pinecone.h"

PineCone::PineCone(sf::Vector2f startPos, Enemy *target)
{
    //load texture
    if(!mTexture.loadFromFile("resources/coneSquirrel.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    sprite.setTexture(mTexture);
    sprite.setPosition(startPos);

    mSpeed = 50;

    if(target) 
    {
        sf::Vector2f dir = target->getPosition() - startPos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        velocity = (length != 0) ? (dir / length) * speed : sf::Vector2f(0.f, 0.f);
    }
}

void PineCone::update(float deltaTime)
{
    mSprite.move(velocity * deltaTime);
}

bool PineCone::hasHitTarget() const
{
    return target && sprite.getGlobalBounds().intersects(target->getBounds());
}

bool PineCone::outOfRange(const sf::FloatRect& bounds) const
{
    return !bounds.intersects(sprite.getGlobalBounds());
}
