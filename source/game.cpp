/**
 * @file game.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for Game.h
 * @date 2025-04-09
 */
#include "../include/game.h"
#include "../include/tower.h"

void Game::checkTowerRanges()
{
    //iterate through towers
    for(size_t i = 0; i < placedTowers.size(); i++)
    {
        sf::Vector2f towerPos = placedTowers[i]->getPosition();
        float towerRange = placedTowers[i]->getRadius();
        //iterate through enemies
        for(size_t j = 0; j < currentEnemies.size(); j++)
        {
            if (currentEnemies[j] != nullptr) {
                sf::Vector2f enemyPos = currentEnemies[j]->getSprite().getOrigin();
                //(towerRange)^2 = (towerPos.x - enemyPos.x)^2 + (towerPos.y - enemyPos.y)^2
                if(pow(static_cast<float>(abs(towerPos.x - enemyPos.x)), 2) + pow(static_cast<float>(abs(towerPos.y - enemyPos.y)), 2) < pow(towerRange, 2))
                {
                    placedTowers[i]->addTarget(currentEnemies[j]);
                }
            }
        }
    }
}

void Game::clearEnemies()
{
    // Delete any remaining enemy pointers to prevent memory leaks
    for (size_t i = 0; i < currentEnemies.size(); ++i) {
        if (currentEnemies[i] != nullptr) {
            delete currentEnemies[i];
            currentEnemies[i] = nullptr;
        }
    }
    
    // Clear the vector
    currentEnemies.clear();
}

void Game::clearTowers()
{
    // Delete any remaining tower pointers to prevent memory leaks
    for (size_t i = 0; i < placedTowers.size(); ++i) {
        if (placedTowers[i] != nullptr) {
            delete placedTowers[i];
            placedTowers[i] = nullptr;
        }
    }
    
    // Clear the vector
    placedTowers.clear();
}