#ifndef RULES_H
#define RULES_H
#include "states.h"
#include "button.h"

class Rules{

public:
    Rules();
    State RulesUpdate(sf::Event& e, sf::RenderWindow& window);
    void draw(sf::RenderWindow &window);

private:
    sf::Text mText;
    sf::Font mFont;

    Button mMenu;
    Button mPlay;

private:


};
#endif