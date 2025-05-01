#include "../include/menu.h"

Menu::Menu(){
    mRules.setText("Rules");
    mRules.setPosition(sf::Vector2f(200.f,300.f));
    mRules.setSize(sf::Vector2f(200.f, 71.f));
    mRules.setColor(sf::Color::Green);
    mRules.setColorTextHover(sf::Color::Green);
    mRules.setColorTextNormal(sf::Color::Blue);

    mPlay.setText("Play");
    mPlay.setPosition(sf::Vector2f(600.f,300.f));
    mPlay.setSize( sf::Vector2f(200.f, 71.f));
    mPlay.setColor(sf::Color::Red);
    mPlay.setColorTextHover(sf::Color::Red);
    mPlay.setColorTextNormal(sf::Color::Green);

    if (!mFont.loadFromFile("resources/college.ttf")){
        std::cout<<"Error opening file\n";
        exit(2);
    }
    mText.setFont(mFont);
    //choose the font size based on button size (I choose half)
    mText.setCharacterSize(25);
    //set label
    mText.setString("Squirrel Tower Defense!");
    mText.setPosition(sf::Vector2f(280.f,100.f));
}

State Menu::MenuUpdate(sf::Event& e, sf::RenderWindow& window){
    if(mRules.update(e, window)){
        return RULES;
    }
    if(mPlay.update(e, window)){
        return GAME;
    }
    return MENU;
}


void Menu::draw(sf::RenderWindow &window){
    window.draw(mText);
    window.draw(mRules);
    window.draw(mPlay);
}