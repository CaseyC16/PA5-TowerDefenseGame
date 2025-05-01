#ifndef BRANCHSPIKE_H
#define BRANCHSPIKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "tower.h"

class BranchSpike : public Tower  //tower that drops branches to impale enemies
{
public:
    BranchSpike(sf::Vector2f position); //constructor
    virtual void attack(std::queue<Enemy> &q); //removes 1 hp from first enemy in queue
};

#endif