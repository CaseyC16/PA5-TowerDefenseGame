#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <queue>
#include "../include/enemyclass.h"

class Tower
{
public:
    void setPosition(sf::Vector2f position) {mPos = position;}
    sf::Vector2f getPosition() const {return mPos;}
    virtual ~Tower() = default;
    void addTarget(Enemy e); //gets called in main every time an enemy enters the radius
    void removeTarget(Enemy e); //gets called in main every time an enemy leaves the radius
    virtual void attack(std::queue<Enemy> &q) = 0;      //pure virtual function that accepts an Enemy object by reference
                                              //and decrements its health according to the implementation of the 
                                              //specific tower. Could also accept a queue holding all the enemies
                                              //in the tower's' range.
    void draw(sf::RenderWindow &window);
protected:   
    Tower() {}; //default constructor - can only be called by child classes
    float mRadius {0.0};  //set in children classes
    sf::Texture mTexture {};
    //TestSprite mSprite; //tower sprite
    sf::Sprite mSprite {};
    sf::Vector2f mPos {0.f,0.f};
    int mFireRate {0};
    int mDamage {0};
    std::queue<Enemy> mTargets;
};

class BranchSpike : public Tower  //tower that drops branches to impale enemies
{
public:
    BranchSpike(sf::Vector2f position); //constructor
};

class ConeBomb : public Tower     //tower that throws exploding pinecones
{
public:
    ConeBomb(sf::Vector2f position); //constructor
};

#endif