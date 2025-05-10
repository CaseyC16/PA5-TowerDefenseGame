/**
 * @file game.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for Game.h
 * @date 2025-04-09
 */
#include "../include/game.h"
#include "../include/tower.h"

/**
 * @brief checks tower range
 * 
 */
void Game::checkTowerRanges(float &deltaTime)
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

    //mTimeSinceLastShot += deltaTime;
    
    //iterate through towers
    for(size_t i = 0; i < placedTowers.size(); i++)
    {
        //make sure tower exists and skip tower if on cooldown
        if (!placedTowers[i] || (towerCooldowns[i] > 0 && i < towerCooldowns.size()))
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
        if(closestEnemy != nullptr)
        {
            std::cout << "Enemy in Range!! Shooting enemy!!\n";
            placedTowers[i]->shoot(closestEnemy, currentBullets);
            deltaTime = 0.f; //reset deltaTime
            
            //set cooldown for tower
            if (i < towerCooldowns.size()) 
            {
                towerCooldowns[i] = placedTowers[i]->getFireRate(); //set cooldown based on tower type
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

/**
 * @brief clear tower vector
 * 
 */
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

/**
 * @brief clear bullet vector
 * 
 */
void Game::clearBullets()
{
    // make a temp vector to help read just the bullet vector
    std::vector<PineCone*> tempBullets;
    for (size_t i = 0; i < currentBullets.size(); ++i) 
    {
        if (currentBullets[i] != nullptr) 
        {
            // if the bullets are going to hit an enemy delete the bullets because they have been used
            if (currentBullets[i]->isMarked()) 
            {
                delete currentBullets[i];
            }
            // keep the bullets that have not targeted an enemy yet
            else 
            {
                tempBullets.push_back(currentBullets[i]);
            }
        }
    } 

    currentBullets = tempBullets;
}

/**
 * @brief update bullets
 * 
 * @param updatedBullets 
 */
void Game::updateBullets(const std::vector<PineCone*>& updatedBullets)
{
    //clean vector
    currentBullets.clear();
    
    for (size_t i = 0; i < updatedBullets.size(); ++i) 
    {
        if (updatedBullets[i] != nullptr && !updatedBullets[i]->isMarked()) 
        {
            currentBullets.push_back(updatedBullets[i]);
        }
        else 
        {
            delete updatedBullets[i];  // Ensure proper memory cleanup
        }
    }
}

/**
 * @brief this function clears enemies that have been marked for deletion
 * 
 */
void Game::clearEnemies() 
{
    std::vector<Enemy*> tempEnemies;

    for (size_t i = 0; i < currentEnemies.size(); ++i) 
    {
        if (currentEnemies[i] != nullptr) 
        {
            // delete enemies that have been marked
            if (currentEnemies[i]->isMarked()) 
            {
                delete currentEnemies[i];
            } 
            // keep enemies that have not been marked
            else 
            {
                tempEnemies.push_back(currentEnemies[i]);
            }
        }
    }

    currentEnemies = tempEnemies;
}

/**
 * @brief update enemy vector
 * 
 * @param updatedEnemies 
 */
void Game::updateEnemies(const std::vector<Enemy*>& updatedEnemies)
{
    //clean vector
    currentEnemies.clear();
    
    for (size_t i = 0; i < updatedEnemies.size(); ++i) 
    {
        if (updatedEnemies[i] != nullptr) 
        {
            currentEnemies.push_back(updatedEnemies[i]);
        }

    }
}