#ifndef ARCHERSQUIRREL_H
#define ARCHERSQUIRREL_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "tower.h"

class ArcherSquirrel : public Tower  //tower that drops branches to impale enemies
{
public:
    ArcherSquirrel(sf::Vector2f position); //constructor
    virtual void attack(std::queue<Enemy> &q); //removes 1 hp from first enemy in queue
    virtual bool placeTower(Tower *tower, sf::Vector2f position, std::vector<Tower*> &placedTowers, int &currency, sf::FloatRect mapBounds);
};

#endif