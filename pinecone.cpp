#include "../include/pinecone.h"

Pinecone::Pinecone(sf::Vector2f startPos, Enemy* target, float speed, float damage, sf::Texture& texture)
    : target(target), speed(speed), damage(damage)
{
    sprite.setTexture(texture);
    sprite.setPosition(startPos);

    if (target) {
        sf::Vector2f dir = target->getPosition() - startPos;
        float length = std::sqrt(dir.x * dir.x + dir.y * dir.y);
        velocity = (length != 0) ? (dir / length) * speed : sf::Vector2f(0.f, 0.f);
    }
}

void Pinecone::update(float deltaTime) {
    sprite.move(velocity * deltaTime);
}

bool Pinecone::hasHitTarget() const {
    return target && sprite.getGlobalBounds().intersects(target->getBounds());
}

bool Pinecone::outOfRange(const sf::FloatRect& bounds) const {
    return !bounds.intersects(sprite.getGlobalBounds());
}

sf::Sprite& Pinecone::getSprite() {
    return sprite;
}