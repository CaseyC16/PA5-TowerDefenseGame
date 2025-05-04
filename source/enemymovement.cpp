#include "../include/enemymovement.h"
#include <cmath>

//sets waypoints for enemy
EnemyMovement::EnemyMovement(sf::Vector2f start)
{
        // waypoints for the enemies to traverse
        waypoints.push_back(sf::Vector2f(52.5f, 20.0f));  // first
        waypoints.push_back(sf::Vector2f(105.0f, 70.0f)); // second
        waypoints.push_back(sf::Vector2f(128.0f, 110.0f)); // third
        waypoints.push_back(sf::Vector2f(402.5f, 220.0f)); // final path

        endPos = waypoints.back();
}

//spawns the enemy wave
void EnemyMovement::spawnWave(const std::vector<enemyType> & wave)
{
    // delete the old enemies from the past wave
    for(std::size_t i = 0; i < activeEnemies.size(); ++i)
    {
        delete activeEnemies[i];
    }
    activeEnemies.clear();

    //spawns 1 enemy at a time and assigns a spawn location and first waypont
    for(std::size_t i = 0; i < wave.size(); ++i) 
    {
        enemyType enemytype = wave[i];
        Enemy* enemy = new Enemy(enemytype);
        enemy->getSprite().setPosition(startPos); 
        enemy->setCurrentWaypoint(0);             
        activeEnemies.push_back(enemy);
    }
}

//updates the movement for the enemy
void EnemyMovement::updateMovement(Enemy& enemy)
{
    // get the enemys current waypoint index
    int currentWayPoint = enemy.getCurrentWaypoint();
    
    // checks to make sure that the enemy has not gotten to the last waypoint
    // gets the current waypoint that the enemy is headed to and the enemies position
    // then calculates the distance left before the waypoint
    if (currentWayPoint < static_cast<int>(waypoints.size()))
    {
        sf::Vector2f target = waypoints[currentWayPoint];
        sf::Vector2f currentPos = enemy.getSprite().getPosition();
        sf::Vector2f direction = target - currentPos;
        float distance = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // how far an enemy can move per step
        float movement = static_cast<float>(enemy.getSpeed());

        // if the enemy is not close enough to the waypoint
        if (distance > movement) 
        {
            // look for direction to head towards
            direction /= distance; 
            enemy.getSprite().move(direction * movement);
        }
        // if the enemy is close enough to the waypoint move on to the next waypoint
        else 
        {   
            direction /= distance; 
            enemy.getSprite().move(direction * movement);

            //make sure that enemy doesnt pass the waypoint after it moves
            enemy.getSprite().setPosition(target);
            enemy.setCurrentWaypoint(currentWayPoint + 1);
        }
    }
}

//moves enemies
void EnemyMovement::updateEnemies()
{
    // updates each enemies movement
    for (std::size_t i = 0; i < activeEnemies.size(); ++i)
    {
        updateMovement(*activeEnemies[i]);
    }
}

//draws the enemy movement
void EnemyMovement::drawEnemies(sf::RenderWindow & window)
{
    //alongside the updateEnemies draws the sprites moving
    for (std::size_t i = 0; i < activeEnemies.size(); ++i)
    {
        activeEnemies[i]->drawSprite(window);
    }
}