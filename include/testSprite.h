/**
 * @file testSprite.h
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Used to Manage the Sprites that Appear On Screen
 * @date 2025-04-09
 */

#ifndef TESTSPRITE_H
#define TESTSPRITE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../include/button.h"

//enum state {normal, hovered, clicked};

class TestSprite: public sf::Drawable
{
public:
    //Default constructor that loads sprite from file “testTree.png”.
    TestSprite();
    //Constructor that sets sprite position to the position, sprite size to size (given in pixels), and sprite color to color.
    TestSprite(std::string fileName, sf::Vector2f position, sf::Vector2f size);
    ~TestSprite(){}; //empty destructor
    //change sprite position to position
    void setPosition(sf::Vector2f position);
    //change sprite size to size
    void setSize(sf::Vector2f  size);
    //change sprite color to color
    void setColor(sf::Color btnColor);
    void setTexture(sf::Texture tex);
    
    sf::Sprite getSprite() {return mSprite;}
    sf::Vector2f getPosition(){return mPosition;}
    sf::Vector2f getDimensions(){return sf::Vector2f(mSprite.getGlobalBounds().width, mSprite.getGlobalBounds().height);}
    sf::Uint32 getState(){return mSprState;}

    //This function update the sprite state and/or look
    // void update(sf::Event& e, sf::RenderWindow& window);
    virtual void draw(sf::RenderTarget& target,sf::RenderStates states) const;
    //void draw(sf::RenderWindow window, sf::Sprite spr);

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Color mSpriteColor;
    sf::Vector2f mPosition;
    sf::Uint32 mSprState;
};
#endif