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
#include "pinecone.h"

class Tower; //forward declaration for Tower class

class Game
{
public:
    void checkTowerRanges();
    std::vector<Enemy*> getEnemies() const {return currentEnemies;};
    std::vector<Tower*> getTowers() const {return placedTowers;}
    std::vector<PineCone*> getBullets() const {return currentBullets;}
    int getNumOfEnemies() const {return currentEnemies.size();}
    int getNumOfTowers() const {return placedTowers.size();}
    void addEnemy(Enemy* newEnemy) {currentEnemies.push_back(newEnemy);}
    void addBullet(PineCone *newBullet) {currentBullets.push_back(newBullet);}
    void clearEnemies();
    void clearTowers();
    void clearBullets();
    void addTower(Tower* newTower) {placedTowers.push_back(newTower);}
    void updateEnemies(const std::vector<Enemy*>& updatedEnemies);
    void updateBullets(const std::vector<PineCone*>& updatedBullets);
private:
    std::vector<Enemy*> currentEnemies;
    std::vector<Tower*> placedTowers;
    std::vector<PineCone*> currentBullets;
};

#endif