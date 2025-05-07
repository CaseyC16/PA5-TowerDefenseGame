/**
 * @file game.h
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Used to Manage Game Elements such as tower functionality and enemy manipulation
 * @date 2025-04-09
 */

#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include "enemyclass.h"

class Tower; //forward declaration for Tower class

class Game
{
public:
    /* iterate through towers - if an enemy is in tower range, then add it to tower's enemy vector
    */
    void checkTowerRanges();
    std::vector<Enemy*> getEnemies() const {return currentEnemies;};
    std::vector<Tower*> getTowers() const {return placedTowers;}
    int getNumOfEnemies() const {return currentEnemies.size();}
    int getNumOfTowers() const {return placedTowers.size();}
    void addEnemy(Enemy* newEnemy) {currentEnemies.push_back(newEnemy);}
    void clearEnemies();
    void clearTowers();
    void addTower(Tower* newTower) {placedTowers.push_back(newTower);}
    void removeTower(Tower* deadTower);
    void updateEnemies(const std::vector<Enemy*>& updatedEnemies) {currentEnemies = updatedEnemies;}
private:
    std::vector<Enemy*> currentEnemies;
    std::vector<Tower*> placedTowers;
};

#endif