/**
 * @file tower.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for tower.h
 * @date 2025-04-09
 */

#include "../include/tower.h"
#include "../include/game.h"

bool Tower::checkBounds(sf::Vector2f position, sf::FloatRect mapBounds, std::vector<Tower*> placedTowers)
{
    //Check if sprite would be placed on the map
    if(!mapBounds.contains(position))
    {
        std::cout << "Outside board\n";
        std::cout << "Tried to place at x = " << position.x << ", y = " << position.y << std::endl;
        return false;
    }

    //check for intersection with other towers
    for(size_t i = 0; i < placedTowers.size(); i++)
    {
        if(abs(position.x - placedTowers[i]->getPosition().x) < 60 && abs(position.y - placedTowers[i]->getPosition().y) < 60)
        {
            std::cout << "Too close to Tower " << i <<std::endl;
            std::cout << "Tried to place at x = " << position.x << ", y = " << position.y << std::endl;
            std::cout << "Distance X = " << abs(position.x - placedTowers[i]->getPosition().x) << std::endl;
            std::cout << "Distance Y = " << abs(position.y - placedTowers[i]->getPosition().y) << std::endl;
            return false;        
        }
    }

    //define path array - could maybe define as global constant instead
    int pathArray[11][11] = {{0,0,1,0,0,0,0,0,0,0,0},
                             {0,0,1,0,0,0,0,0,0,0,0},
                             {0,0,1,1,1,1,1,1,1,1,1},
                             {0,0,1,0,0,1,0,0,0,0,1},
                             {0,0,1,0,0,1,0,0,0,0,1},
                             {0,0,1,0,0,1,0,0,0,0,1},
                             {0,0,1,0,0,1,0,0,0,0,1},
                             {0,0,1,0,0,1,0,0,0,0,1},
                             {0,0,1,1,1,1,1,1,1,1,1},
                             {0,0,0,0,0,0,0,0,0,0,0},
                             {0,0,0,0,0,0,0,0,0,0,0}};
    double blockWidth = 63.6364;
    double blockHeight = 36.36364;
    if(pathArray[static_cast<int>(position.y/blockHeight)][static_cast<int>(position.x/blockWidth)])
    {
        std::cout << "Too close to path\n";
        std::cout << "Path array value: " << pathArray[static_cast<int>(position.x/blockWidth)][static_cast<int>(position.y/blockHeight)] << std::endl;
        std::cout << "Array row index = " << static_cast<int>(position.x/blockWidth) << std::endl;
        std::cout << "Array column index = " << static_cast<int>(position.y/blockHeight) << std::endl;
        std::cout << "Tried to place at x = " << position.x << ", y = " << position.y << std::endl;
        return false;
    }

    return true;
}

void Tower::addTarget(Enemy *e)
{
    mTargets.push_back(e);
}

void Tower::removeTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy leaves the radius
    //mTargets.pop();
}

void Tower::draw(sf::RenderWindow &window)
{
    window.draw(mSprite);
}

void Tower::shoot(Enemy *target)
{
    //make Bullet object and add to Bullet vector
    PineCone *newBullet = new PineCone(this->getPosition(), target);
}