/**
 * @file tower.cpp
 * @author Joseph Moran
 * @brief Implimentation File for tower.h
 * @date 2025-04-09
 */

#include "../include/tower.h"
#include "../include/game.h"

/**
 * @brief checks bounds for tower placement
 * 
 * @param position  tower position
 * @param mapBounds  boundary of map
 * @param placedTowers  placed towers
 * @return true 
 * @return false 
 */
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

/**
 * @brief add enemy to vector
 * 
 * @param e 
 */
void Tower::addTarget(Enemy *e)
{
    mTargets.push_back(e);
}

/**
 * @brief remove enemy from vector
 * 
 * @param e 
 */
void Tower::removeTarget(Enemy e)
{
    //have a piece of code in main that detects when an enemy leaves the radius
    //mTargets.pop();
}

/**
 * @brief draw enemy
 * 
 * @param window 
 */
void Tower::draw(sf::RenderWindow &window)
{
    window.draw(mSprite);

    //draw range radius as transparent circle
    if (mRadius > 0)
    {
        sf::CircleShape rangeCircle(mRadius);
        rangeCircle.setOrigin(sf::Vector2f(mRadius, mRadius));
        rangeCircle.setPosition(mPos);
        rangeCircle.setFillColor(sf::Color(0, 255, 0, 20)); // Transparent green
        rangeCircle.setOutlineColor(sf::Color(0, 255, 0, 40)); // Slightly less transparent green
        rangeCircle.setOutlineThickness(2);
        window.draw(rangeCircle);
    }
}

/**
 * @brief shoot at enemy
 * 
 * @param target  enemy
 * @param gameBullets  vector of bullets
 */
void Tower::shoot(Enemy *target, std::vector<PineCone*> &gameBullets)
{
    //check if target exists
    if (!target || target->getHealth() <= 0)
    {
        return;
    }

    //make pinecone object and add to Bullet vector
    sf::Vector2f startPos = this->getPosition();
    PineCone *newBullet = new PineCone(startPos, target);
    gameBullets.push_back(newBullet);

    //point bullet at enemy

}