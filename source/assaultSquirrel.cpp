/**
 * @file archerSquirrel.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for archerSquirrel.h
 * @date 2025-04-09
 */

#include "../include/assaultSquirrel.h"
#include "../include/game.h"

AssaultSquirrel::AssaultSquirrel(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/machineGunSquirrelFinalProject2025(rightFace).png"))
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
    mRadius = 25;
    mPos = position;
    mFireRate = 15; //sleep 15 seconds between attacks
    //mDamage = 10; //destroy all enemies in range
    mSprite.setPosition(mPos);
    mCost = 200;
}

void AssaultSquirrel::attack(std::queue<Enemy> &q)
{
    //destroy all enemies in range
    while(!q.empty())
    {
        Enemy temp = q.front();
        int health = temp.getHealth();
        if(health < 2)
        {
            q.pop(); //only remove enemy from queue if it's about to be destroyed
        }
        //shoot at enemy
        temp.targeted();
    }
}

bool AssaultSquirrel::placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds)
{
    //Check if position is on the map
    if(!checkBounds(position, mapBounds, currentGame.getTowers()))
    {
        std::cout << "Invalid placement - click again on a valid location to place tower." << std::endl;
        return false;
    }

    //Check if player has enough currency
    if(currency < 200)
    {
        std::cout << "Not enough currency to place tower." << std::endl;
        return false;
    }

    Tower *newTower = new AssaultSquirrel(sf::Vector2f(position));
    std::cout << "Placed Assault Squirrel at x = " << position.x << ", y = " << position.y << std::endl;
    currentGame.addTower(newTower);
    currency -= 200;
    return true;
}