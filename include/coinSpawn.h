#ifndef COINSPAWN_H
#define COINSPAWN_H
#include <SFML/Graphics.hpp>
#include "enemyclass.h"

class Coin: public Enemy{

public:
    Coin(){};
    
    // sf::Sprite & getSprite() {return mSprite;}
    // void setSprite(const std::string & sprite);
    // void drawSprite(sf::RenderWindow & window);

    // int getCurrentWaypoint() const { return mCurrentWaypoint; }
    // void setCurrentWaypoint(int waypoint);
    // void updateMovement(const std::vector<sf::Vector2f>& waypoints);

   //destructor
    ~Coin(){}; //every time an enemy is destroyed make player earn currency

private:

    // int mCurrentWaypoint;
    // sf::Sprite mSprite;
    // sf::Texture mTexture;
    // enemyType mType;
};

#endif