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
            sf::Vector2f enemyPos = currentEnemies[j]->getSprite().getOrigin();
            //(towerRange)^2 = (towerPos.x - enemyPos.x)^2 + (towerPos.y - enemyPos.y)^2
            if(pow(static_cast<float>(abs(towerPos.x - enemyPos.x)), 2) + pow(static_cast<float>(abs(towerPos.y - enemyPos.y)), 2) < pow(towerRange, 2))
            {
                placedTowers[i]->addTarget(currentEnemies[j]);
            }
        }
    }
}

void Game::clearEnemies()
{
    while(!currentEnemies.empty())
    {
        currentEnemies.pop_back();
    }
}

void Game::clearTowers()
{
    while(!placedTowers.empty())
    {
        placedTowers.pop_back();
    }
}