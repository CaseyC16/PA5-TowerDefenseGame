/**
 * @file assaultSquirrel.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for assaultSquirrel.h
 * @date 2025-04-09
 */

#include "../include/archerSquirrel.h"
#include "../include/game.h"

/**
 * @brief Construct a new Archer Squirrel:: Archer Squirrel object
 * 
 * @param position 
 */
ArcherSquirrel::ArcherSquirrel(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/bowSquirrelFinalProject2025(RightFace).png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX =  60.0f / textureSize.x;
    float scaleY = 60.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));

    //set origin to center
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f));
    mRadius = 80;
    mPos = position;
    mFireRate = 10; //sleep 10 seconds between attacks
    //mDamage = 10; //take 1 hp from first 10 enemies
    mSprite.setPosition(mPos);
    mCost = 160;
}

/**
 * @brief attacks an enemy
 * 
 * @param q 
 */
void ArcherSquirrel::attack(std::queue<Enemy> &q)
{
    //take one hp from all enemies
    while(!q.empty())
    {
        Enemy temp = q.front(); //save enemy in case it is destroyed by attack
        // int health = temp.getHealth();
        q.pop(); //remove enemy from queue
        temp.targeted(); //shoot at enemy
    }
}

/**
 * @brief places tower
 * 
 * @param tower 
 * @param position 
 * @param currentGame 
 * @param currency 
 * @param mapBounds 
 * @return true 
 * @return false 
 */
bool ArcherSquirrel::placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds)
{
    //Check if position is on the map
    if(!checkBounds(position, mapBounds, currentGame.getTowers()))
    {
        std::cout << "Invalid placement - click again on a valid location to place tower." << std::endl;
        return false;
    }

    //Check if player has enough currency
    if(currency < mCost)
    {
        std::cout << "Not enough currency to place tower." << std::endl;
        return false;
    }

    Tower *newTower = new ArcherSquirrel(sf::Vector2f(position));
    std::cout << "Placed Archer Squirrel at x = " << position.x << ", y = " << position.y << std::endl;
    currentGame.addTower(newTower);
    currency -= mCost;
    return true;
}