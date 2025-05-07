/**
 * @file testSprite.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Implimentation File for testSprite.h
 * @date 2025-04-09
 */

#include "../include/testSprite.h"

//Constructor that sets sprite position to the position,  sprite size to size (given in pixels), and sprite color to color
TestSprite::TestSprite(std::string fileName, sf::Vector2f position, sf::Vector2f size)
{
    if(!mTexture.loadFromFile(fileName))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    //create sprite that looks like a tree
    mSprite.setTexture(mTexture);
    
    //get size of image
    sf::Vector2u imageSize=mTexture.getSize();
    //change origin to the center of the image (makes rotation easy)
    mSprite.setOrigin(imageSize.x/2, imageSize.y/2);
    //set position
    mPosition = position;
    mSprite.setPosition(mPosition.x,mPosition.y);
    //choose color
    // mSpriteColor = color;
    //mSprite.setColor(sf::Color::Red);
    //set size as a ratio of original size
    mSprite.setScale(size.x/imageSize.x, size.y/imageSize.y);

    //set button state
    mSprState = normal;
}

//Default constructor
TestSprite::TestSprite() : TestSprite("resources/testTree.png", sf::Vector2f(300.f,100.f), sf::Vector2f(100.f,100.f))
{
    //set scale to 100%
    mSprite.setScale(1, 1);
}

//void TestSprite::update(sf::Event& e, sf::RenderWindow& window)
//{
    //sf::Vector2i mPos = sf::Mouse::getPosition(window);
    //sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);
    //bool mouseInButton =    mousePosition.x >= mSprite.getPosition().x - mSprite.getGlobalBounds().width/2
                            //&& mousePosition.x <= mSprite.getPosition().x + mSprite.getGlobalBounds().width/2
                            //&& mousePosition.y >= mSprite.getPosition().y - mSprite.getGlobalBounds().height/2
                            //&& mousePosition.y <= mSprite.getPosition().y + mSprite.getGlobalBounds().height/2;
//}

void TestSprite::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

//change button position to position
void TestSprite::setPosition(sf::Vector2f position)
{
    //update position
    mPosition = position;
    //move button
    mSprite.setPosition(mPosition);
}

//change button size to size
void TestSprite::setSize(sf::Vector2f size)
{
    //get size of image
    sf::Vector2u imageSize=mTexture.getSize();
    //set size as a ratio of original size
    mSprite.setScale(size.x/imageSize.x, size.y/imageSize.y);
}

//change button color to color
void TestSprite::setColor(sf::Color sprColor)
{
    //update color
    mSpriteColor = sprColor;
    mSprite.setColor(mSpriteColor);
}

void TestSprite::setTexture(sf::Texture tex)
{
    mTexture = tex;
}
