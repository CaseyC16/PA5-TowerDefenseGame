#ifndef COINSPAWN_H
#define COINSPAWN_H
#include <SFML/Graphics.hpp>
#include "enemyclass.h"

class Coin:public sf::Transformable{

public:
    Coin();
    Coin(sf::Vector2f &pos);
    void drawSprite(sf::RenderWindow & window);
    sf::Sprite & getSprite() {return mCoinSprite;}
   //destructor
    ~Coin(){}; //every time an enemy is destroyed make player earn currency

private:
    sf::Sprite mCoinSprite;
    sf::Texture mCoinTexture;
};

#endif