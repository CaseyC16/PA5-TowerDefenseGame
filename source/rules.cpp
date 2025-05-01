#include "../include/rules.h"

Rules::Rules(){
    mMenu.setText("Menu");
    mMenu.setPosition(sf::Vector2f(200.f,300.f));
    mMenu.setSize(sf::Vector2f(200.f, 71.f));
    mMenu.setColor(sf::Color::Green);
    mMenu.setColorTextHover(sf::Color::Green);
    mMenu.setColorTextNormal(sf::Color(95,25,10));

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
    mText.setCharacterSize(20);
    //set label
    mText.setString("Explaning squirrel rules");
}

State Rules::RulesUpdate(sf::Event& e, sf::RenderWindow& window){
    if(mMenu.update(e, window)){
        return MENU;
    }
    if(mPlay.update(e, window)){
        return GAME;
    }
    return MENU;
}


void Rules::draw(sf::RenderWindow &window){
    window.draw(mText);
    window.draw(mMenu);
    window.draw(mPlay);
}