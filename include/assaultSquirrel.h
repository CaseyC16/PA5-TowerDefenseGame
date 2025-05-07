#ifndef ASSAULTSQUIRREL_H
#define ASSAULTSQUIRREL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "tower.h"
#include "game.h"

class AssaultSquirrel : public Tower  //tower that drops branches to impale enemies
{
public:
    AssaultSquirrel(sf::Vector2f position); //constructor
    virtual void attack(std::queue<Enemy> &q); //removes 1 hp from first enemy in queue
    virtual bool placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds);
};

#endif