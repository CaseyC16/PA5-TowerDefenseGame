#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#define TEXTURE_LOADING_ERROR 2

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
//make an enum for a debuff state and normal state
//enum state {normal, debuff};
//make an enum for if the enemy got killed by a tower 
//make an enum for enemy types
enum enemyType {peasant, knight, heavyKnight};


class Enemy
{
    public:
    //constructor for class to set default health and speed
    Enemy(enemyType type);
    Enemy(){};
    //getter and setter functions
        //health
        int getHealth(){return mHealth;}
        void setHealth(int newhealth);

        //speed
        int getSpeed(){return mSpeed;}
        void setSpeed(int newspeed);

        //change type of enemy
        enemyType getType() const {return mType;}
        void setType(enemyType newType);

        //enemy sprite
        sf::Sprite & getSprite() {return mSprite;}
        void setSprite(const std::string & sprite);
        void drawSprite(sf::RenderWindow & window);

        //enemy waypoints
        //int getCurrentWaypoint() const { return mCurrentWaypoint; }
        //void setCurrentWaypoint(int index) { mCurrentWaypoint = index; }

    //towers target enemies
    void targeted();

    //moves the enemies
    int getCurrentWaypoint() const { return mCurrentWaypoint; }
    void setCurrentWaypoint(int waypoint);
    void updateMovement(const std::vector<sf::Vector2f>& waypoints);
    //static void EnemyMovementPath();
    
    //define vectors for waypoints
    //static std::vector<sf::Vector2f> waypoints;
    //static sf::Vector2f startPos;

    //destructor
    ~Enemy(); //every time an enemy is destroyed make player earn currency

    protected:

    int mHealth;
    int mSpeed;
    int mCurrentWaypoint;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    enemyType mType;
};

#endif //guard code