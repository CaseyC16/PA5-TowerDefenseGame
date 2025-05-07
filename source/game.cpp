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
    //tower cooldown (avoid rapid fire)
    static std::vector<float> towerCooldowns(placedTowers.size(), 0.0f);
    if(towerCooldowns.size() < placedTowers.size())
    {
        towerCooldowns.resize(placedTowers.size(), 0.0f);
    }
    
    //reduce cooldowns
    for (size_t i = 0; i < towerCooldowns.size(); ++i)
    {
        if (towerCooldowns[i] > 0)
        {
            towerCooldowns[i] -= 0.1f;
        }
    }
    
    //iterate through towers
    for(size_t i = 0; i < placedTowers.size(); i++)
    {
        //skip tower if on cooldown
        if(i < towerCooldowns.size() && towerCooldowns[i] > 0)
        {
            continue;
        }
        
        sf::Vector2f towerPos = placedTowers[i]->getPosition();
        float towerRange = placedTowers[i]->getRadius();
        
        //find closest enemy
        Enemy* closestEnemy = nullptr;
        float closestDistance = towerRange * towerRange; //range^2
        
        //iterate through enemies
        for(size_t j = 0; j < currentEnemies.size(); j++)
        {
            if (currentEnemies[j] != nullptr) {
                sf::Vector2f enemyPos = currentEnemies[j]->getSprite().getPosition();
                
                //find squared distance
                float dx = towerPos.x - enemyPos.x;
                float dy = towerPos.y - enemyPos.y;
                float distanceSquared = dx*dx + dy*dy;
                
                if(distanceSquared < closestDistance)
                {
                    closestDistance = distanceSquared;
                    closestEnemy = currentEnemies[j];
                }
            }
        }
        
        //shoot enemy if found
        if(closestEnemy)
        {
            std::cout << "Enemy in Range!! Shooting enemy!!\n";
            placedTowers[i]->shoot(closestEnemy, currentBullets);
            
            //set cooldown for tower
            if (i < towerCooldowns.size()) {
                towerCooldowns[i] = 1.0f; //1-second cooldown
            }
        }

           //////// 

    //     sf::Vector2f towerPos = placedTowers[i]->getPosition();
    //     float towerRange = placedTowers[i]->getRadius();
    //     //iterate through enemies
    //     for(size_t j = 0; j < currentEnemies.size(); j++)
    //     {
    //         if (currentEnemies[j] != nullptr) {
    //             sf::Vector2f enemyPos = currentEnemies[j]->getSprite().getOrigin();
    //             //(towerRange)^2 = (towerPos.x - enemyPos.x)^2 + (towerPos.y - enemyPos.y)^2
    //             if(pow(static_cast<float>(abs(towerPos.x - enemyPos.x)), 2) + pow(static_cast<float>(abs(towerPos.y - enemyPos.y)), 2) < pow(towerRange, 2))
    //             {
    //                 std::cout << "Enemy in Range!! Shooting enemy!!\n";
    //                 placedTowers[i]->shoot(currentEnemies[j], currentBullets);
    //             }
    //         }
    //     }
    }
}

void Game::clearEnemies()
{
    //delete ptrs
    for (size_t i = 0; i < currentEnemies.size(); ++i) {
        if (currentEnemies[i] != nullptr) {
            delete currentEnemies[i];
            currentEnemies[i] = nullptr;
        }
    }
    
    //clear vector
    currentEnemies.clear();
}

void Game::clearTowers()
{
    //delete ptrs
    for (size_t i = 0; i < placedTowers.size(); ++i) {
        if (placedTowers[i] != nullptr) {
            delete placedTowers[i];
            placedTowers[i] = nullptr;
        }
    }
    
    //clear vector
    placedTowers.clear();
}

void Game::clearBullets()
{
    //delete ptrs
    for (size_t i = 0; i < currentBullets.size(); ++i) {
        if (currentBullets[i] != nullptr) {
            delete currentBullets[i];
            currentBullets[i] = nullptr;
        }
    }
    
    //clear vector
    currentBullets.clear();
}