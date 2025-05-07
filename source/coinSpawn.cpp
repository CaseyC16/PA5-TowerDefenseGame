#include "../include/coinSpawn.h"

Coin::Coin(){
    
    if (!mCoinTexture.loadFromFile("resources/PineCoinForCSFinal.png")){
        exit(TEXTURE_LOADING_ERROR);
    }
    mCoinSprite.setTexture(mCoinTexture);
    mCoinSprite.setScale(0.1f,0.1f);
    mCoinSprite.setPosition(250.0f,200.0f);
    // mCoinSprite.setOrigin(100.0f,50.0f);
}


Coin::Coin(sf::Vector2f &pos){
    if (!mCoinTexture.loadFromFile("resources/PineCoinForCSFinal.png")){
        exit(TEXTURE_LOADING_ERROR);
    }
    mCoinSprite.setTexture(mCoinTexture);
    mCoinSprite.scale(0.1f,0.1f);
    mCoinSprite.setPosition(pos);
    // mCoinSprite.setOrigin(pos);
}

void Coin::drawSprite(sf::RenderWindow & window){
    window.draw(mCoinSprite);
}