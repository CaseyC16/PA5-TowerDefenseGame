/**
 * @file coneThrower.h
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Header File to Manage the ConeThrower Tower
 * @date 2025-04-09
 */

#ifndef CONETHROWER_H
#define CONETHROWER_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include "tower.h"

class ConeThrower : public Tower  //tower that throws individual pinecones
{
public:
    ConeThrower(sf::Vector2f position); //constructor
    virtual void attack(std::queue<Enemy> &q); //removes 1 hp from first enemy in queue
    virtual bool placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds);
};

#endif