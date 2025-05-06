#include "../include/tower.h"

bool Tower::checkPath(sf::Vector2f position, sf::FloatRect mapBounds, std::vector<Tower*> placedTowers)
{
    //Check if sprite would be placed on the map
    if(!mapBounds.contains(position))
    {
        std::cout << "Outside board\n";
        return false;
    }

    //check for intersection with other towers
    for(size_t i = 0; i < placedTowers.size(); i++)
    {
        if(abs(position.x - placedTowers[i]->getPosition().x) < 60 || abs(position.y - placedTowers[i]->getPosition().y) < 60)
        {
            std::cout << "Too close to Tower " << i <<std::endl;
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
    if(pathArray[static_cast<int>(position.x/blockWidth)][static_cast<int>(position.y/blockHeight)])
    {
        std::cout << "Too close to path\n";
        return false;
    }

    return true;
}

void Tower::addTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy enters the radius
    mTargets.push(e);
}

void Tower::removeTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy leaves the radius
    mTargets.pop();
}

void Tower::draw(sf::RenderWindow &window)
{
    window.draw(mSprite);
}