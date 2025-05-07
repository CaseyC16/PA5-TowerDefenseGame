/**
 * @file Button.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran, created from Ekaterina Miller's Lecture
 * @brief Implimentation File for button.h
 * @date 2025-04-09
 */

#include "../include/button.h"

//Constructor that sets button label to s, button position to the position,  button size to size (given in pixels), and button color to color.
Button::Button(std::string s, sf::Vector2f position, sf::Vector2f size, sf::Color color)
{
    if (!mTexture.loadFromFile("resources/button.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    //create sprite that look like a button
    mButton.setTexture(mTexture);
    
    //get size of image
    sf::Vector2u imageSize=mTexture.getSize();
    //change origin to the center of the image (makes rotation easy)
    mButton.setOrigin(imageSize.x/2, imageSize.y/2);
    //set position
    mPosition = position;
    mButton.setPosition(mPosition.x,mPosition.y);
    //choose color
    mButtonColor = color;
    mButton.setColor(mButtonColor);
    //set size as a ratio of original size
    mButton.setScale(size.x/imageSize.x, size.y/imageSize.y);
    //Make label
    if (!mFont.loadFromFile("resources/college.ttf"))
    {
        std::cout<<"Error opening file\n";
        exit(2);
    }
    mText.setFont(mFont);
    //choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setCharacterSize(fontSize);
    //set label
    mText.setString(s);
    //set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    mText.setPosition(mPosition.x, mPosition.y-fontSize/4);
    // //choose colors
    mTextNormal = sf::Color::Green;
    mTextHover = sf::Color::Red;
    mText.setFillColor(mTextNormal);

    //set button state
    mBtnState = normal;
}

//Default constructor that loads texture from file “button.png” and font from “college.ttf” file.
//set texture for mButton, set the origin to the middle of the button (texture), 
//set color to White, position to {300,100}, set state to normal, and scale to 100%
//set font for the text, set the size of the text to the half of Button size, set the origin to the middle of the text 
//and set position at the middle of the button, assign “Push me!” as a string of the button
Button::Button() : Button("Push me!", sf::Vector2f(300,100), sf::Vector2f(100,100), sf::Color::White)
{
    //set scale to 100%
    mButton.setScale(1, 1);
}

bool Button::update(sf::Event& e, sf::RenderWindow& window)
{
    sf::Vector2i mPos = sf::Mouse::getPosition(window);
    sf::Vector2f mousePosition = window.mapPixelToCoords(mPos);
    bool mouseInButton =    mousePosition.x >= mButton.getPosition().x - mButton.getGlobalBounds().width/2
                            && mousePosition.x <= mButton.getPosition().x + mButton.getGlobalBounds().width/2
                            && mousePosition.y >= mButton.getPosition().y - mButton.getGlobalBounds().height/2
                            && mousePosition.y <= mButton.getPosition().y + mButton.getGlobalBounds().height/2;
    if(e.type == sf::Event::MouseMoved)
    {
        if(mouseInButton)
        {
            mText.setFillColor(mTextHover);
        }
        else
        {
            mText.setFillColor(mTextNormal);
        }
    }
    if (e.type == sf::Event::MouseButtonPressed)
    {
        if(e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mButton.setRotation(180);
            }
            else
            {
                mButton.setRotation(0);
            }
        }
    }
    if (e.type == sf::Event::MouseButtonReleased)
    {
        if (e.mouseButton.button==sf::Mouse::Left)
        {
            if(mouseInButton)
            {
                mButton.setRotation(0);
                mText.setFillColor(mTextHover);
                
                return true;
            }
            else
            {
                mText.setFillColor(mTextNormal);
                mButton.setRotation(0);
            }
        }
    }
    return false;
}

void Button::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    target.draw(mButton, states);
    target.draw(mText, states);
}

void Button::setText(std::string s)
{
    //change text
    mText.setString(s);
    //reset to middle of button
    //set origin to the middle
    mText.setOrigin(mButton.getGlobalBounds().width/2, mButton.getGlobalBounds().height/2);
    //set position at the middle of the button
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition(mPosition.x, mPosition.y-fontSize/4);
}

//change button position to position (what else needs to be changed?)
void Button::setPosition(sf::Vector2f position)
{
    //update position
    mPosition = position;
    //move button
    mButton.setPosition(mPosition);
    //move text
    //set origin to the middle
    mText.setOrigin(mButton.getGlobalBounds().width/2, mButton.getGlobalBounds().height/2);
    //set position at the middle of the button
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setPosition(mPosition.x, mPosition.y-fontSize/4);
}

//change button size to size (what else needs to be changed?)
void Button::setSize(sf::Vector2f  size)
{
    //get size of image
    sf::Vector2u imageSize=mTexture.getSize();
    //set size as a ratio of original size
    mButton.setScale(size.x/imageSize.x, size.y/imageSize.y);
    //choose the font size based on button size (I choose half)
    unsigned int fontSize = mButton.getGlobalBounds().height/2;
    mText.setCharacterSize(fontSize);
    //set origin to the middle
    mText.setOrigin(mText.getGlobalBounds().width/2, mText.getGlobalBounds().height/2);
    //set position at the middle of the button
    mText.setPosition(mPosition.x, mPosition.y-fontSize/4);
}

//change button color to color (what else needs to be changed?)
void Button::setColor(sf::Color btnColor)
{
    //update color
    mButtonColor = btnColor;
    mButton.setColor(mButtonColor);
}