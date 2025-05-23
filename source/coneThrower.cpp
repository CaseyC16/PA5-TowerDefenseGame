/**
 * @file coneThrower.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for coneThrower.h
 * @date 2025-04-09
 */

#include "../include/coneThrower.h"
#include "../include/game.h"


/**
 * @brief Construct a new Cone Thrower:: Cone Thrower object
 * 
 * @param position 
 */
ConeThrower::ConeThrower(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/PineConeThrowerSquirrelFinalProject2025(RightFace).png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 60.0f / textureSize.x;
    float scaleY = 60.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));

    //set origin to center
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f));
    mRadius = 100;
    mPos = position;
    mFireRate = 20.f; //cooldown between attacks
    //mDamage = 1; //take one hp from enemy
    mSprite.setPosition(mPos);
    mCost = 100;
}

/**
 * @brief attack enemies
 * 
 * @param q 
 */
void ConeThrower::attack(std::queue<Enemy> &q)
{
    //take one hp from first enemy in queue
    //can call Enemy targeted function instead of manually removing health
    Enemy temp = q.front();
    // int health = temp.getHealth();
    q.pop(); //remove enemy from queue
    temp.targeted(); //shoot at enemy
}

/**
 * @brief place a tower
 * 
 * @param tower tower
 * @param position  
 * @param currentGame 
 * @param currency 
 * @param mapBounds 
 * @return true 
 * @return false 
 */
bool ConeThrower::placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds)
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

    Tower *newTower = new ConeThrower(sf::Vector2f(position));
    std::cout << "Placed ConeThrower at x = " << position.x << ", y = " << position.y << std::endl;
    currentGame.addTower(newTower);
    currency -= mCost;
    return true;
}