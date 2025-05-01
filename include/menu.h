#ifndef MENU_H
#define MENU_H
#include "button.h"
#include "states.h"

class Menu{


public:
    Menu();
    State MenuUpdate(sf::Event& e, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);


private:
    sf::Text mText;
    sf::Font mFont;

    Button mRules;
    Button mPlay;

};

#endif