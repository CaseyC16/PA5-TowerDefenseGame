/**
 * @file pinecone.h
 * @author Joseph Moran
 * @brief Definition file for projectile class
 * @version 0.1
 * @date 2025-05-07
 * 
 * @copyright Copyright (c) 2025
 * 
 */
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
    PineCone(sf::Vector2f startPos, Enemy *target);

    //updates the enemy targeting when an enemy is hit
    void update(float deltaTime, std::vector<Enemy*>& enemies); 
    bool hasHitTarget(Enemy *target) const;
    bool isMarked() const { return markedDelete; }
    bool outOfRange(const sf::FloatRect& bounds) const;

    sf::Sprite& getSprite() {return mSprite;}
    void setPosition(const sf::Vector2f& pos) { mPosition = pos; mSprite.setPosition(pos); }
    
private:
    sf::Sprite mSprite {};
    sf::Texture mTexture {};
    sf::Vector2f mPosition {0.f,0.f};
    sf::Vector2f mVelocity {0.f,0.f};
    float mSpeed {0.f};
    Enemy * mTarget;
    bool markedDelete = false;
};

#endif