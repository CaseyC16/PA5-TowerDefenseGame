/**
 * @file enemyClass.h
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Related to all enemy creation, deletion, movement, and status
 * @date 2025-04-09
 */

#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#define TEXTURE_LOADING_ERROR 2

#include <iostream>
#include <cmath>
#include <vector>
#include <unistd.h>
#include <SFML/Graphics.hpp>

//enum for enemy types
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
        float getSpeed(){return mSpeed;}
        void setSpeed(float newspeed);

        //change type of enemy
        enemyType getType() const {return mType;}
        void setType(enemyType newType);

        //enemy sprite
        sf::Sprite & getSprite() {return mSprite;}
        void setSprite(const std::string & sprite);
        void drawSprite(sf::RenderWindow & window);


    //towers target enemies
    void targeted();

    //moves the enemies
    size_t getCurrentWaypoint() const { return mCurrentWaypoint; }
    void setCurrentWaypoint(int waypoint);
    void updateMovement(const std::vector<sf::Vector2f>& waypoints, float deltaTime);

    bool isMarked() const { return markedDelete; }
    //destructor
    ~Enemy();

    protected:

    int mHealth;
    float mSpeed;
    int mCurrentWaypoint;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    enemyType mType;
    bool markedDelete = false;
};

#endif //guard code