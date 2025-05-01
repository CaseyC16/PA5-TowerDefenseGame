/**
 * @file main.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Balloon Tower Defense Game
 * @date 2025-04-09
 */

 //COMPILE g++ -Wall main.cpp source/*.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 //On Mac: g++ -Wall -std=c++11 main.cpp source/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/sfml@2/lib
#include <iostream>
#include "include/button.h"
#include "include/enemyclass.h"
#include "include/enemymovement.h"
#include "include/coneThrower.h"
#include "include/menu.h"
#include "include/rules.h"
#include "include/states.h"

using std::cout;
using std::endl;
using std::string;

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 400), "Squirrels Tower Defense");
    /* OUTLINE
    Welcome Screen
        Play Button
        How to Play Button

    Game Loop
        Display the Stage and UI
            Current Money
            Current Round
            Available Squirels to Purchase
        Allow Player to Puchase and Place Squirels
        Play Button to Initiate Rounds
            Begin Summoning and Movement of Humans
            Stop Upon the Conclusion of Each Round & Repeat
    */

    /*
        Welcome Screen
            Use Button Class to Make Button Objects w/ interaction when clicked
                One Button Labeled Play, the Other Labeled Rules
                    Play: Takes Player into the Game Loop 
                    Rules: Takes Player into a Screen with How to Play. Keep Same Wallpaper as Title Screen

        Game Loop
            While()
    */
    
    Menu start;
    Rules rules;
    // Game game;
    
   //************************************** */
   //Tower class testing
//    TestSprite Tree1;
//    TestSprite Tree2("resources/testTree.png", sf::Vector2f(700.f,300.f), sf::Vector2f(100.f,100.f));
//    TestSprite Tree3("resources/testTree.png", sf::Vector2f(300.f,200.f), sf::Vector2f(100.f,100.f));
//    ConeThrower Tower1(sf::Vector2f(500.f, 250.f));
   //Tower1.setSprite("resources/testTree.png");
   //************************************** */

    State currentState=MENU;
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::MouseButtonPressed){
            
           // rules.update(event,window);
                switch(currentState){
                    case MENU: currentState=start.MenuUpdate(event,window);
                        break;
                    case RULES: currentState=rules.RulesUpdate(event,window);
                        break;
                    case GAME: //currentState=start.update(event,window);
                        break;
                }
            }
        }
        window.clear();
        //rules.draw(window);
        switch(currentState){
            case MENU: start.draw(window);
                break;
            case RULES: rules.draw(window);
                break;
            case GAME: //currentState=start.update(event,window);
                break;
        }
    //    window.draw(Tree1);
    //    window.draw(Tree2);
    //    window.draw(Tree3);
       //Tower1.draw(window);
       //window.draw(Tower1);
       window.display();
    }


   //************************************** */
   //Tower class testing
//    window.clear();
//    window.draw(Tree1);
//    window.draw(Tree2);
//    window.display();

   //************************************** */

    return 0;

}