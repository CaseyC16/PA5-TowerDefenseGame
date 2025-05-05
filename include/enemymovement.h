#ifndef ENEMYMOVEMENT_H
#define ENEMYMOVEMENT_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "enemyclass.h"

class EnemyMovement
{
    public:
    //constructor for pathing of enemies
    EnemyMovement(sf::Vector2f start);

    void updateEnemies();
    void updateMovement(Enemy& enemy);
    void spawnWave(const std::vector<enemyType> & wave);
    void drawEnemies(sf::RenderWindow & window);

    private:
    sf::Vector2f startPos;
    sf::Vector2f endPos;
    std::vector<Enemy*> activeEnemies;
    std::vector<sf::Vector2f> waypoints; 
};

#endif //guard clause