#ifndef TOWER_H
#define TOWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>

class Tower
{
public:
    void setPosition(sf::Vector2f position) {mPos = position;}
    sf::Vector2f getPosition() const {return mPos;}
    virtual ~Tower() = default;
    //virtual void attack(Enemy &e) = 0;      //pure virtual function that accepts an Enemy object by reference
                                              //and decrements its health according to the implementation of the 
                                              //specific tower. Could also accept a queue holding all the enemies
                                              //in the tower's' range.
protected:   
    Tower(); //default constructor - can only be called by child classes
    int mRadius;  //set in children classes
    //Sprite mSprite; //tower sprite
    sf::Vector2f mPos;
    int mFireRate;
    int mDamage;
};

class ConeThrower : public Tower  //tower that throws individual pinecones
{
public:
    ConeThrower(sf::Vector2f position); //constructor
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