#ifndef PINECONE_H
#define PINECONE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "enemyclass.h"

class PineCone
{
public:
    PineCone() {} //default constructor
    void update(float deltaTime);  // Move toward target
    bool hasHitTarget() const;
    bool outOfRange(const sf::FloatRect& bounds) const;
    sf::Sprite& getSprite() {return mSprite;}
private:
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mPosition {0.f,0.f};
    sf::Vector2f mVelocity {0.f,0.f};
    float mSpeed {0.f};
};

#endif