/**
 * @file main.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Balloon Tower Defense Game
 * @date 2025-04-09
 */

 //COMPILE g++ -Wall source/*.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 //On Mac: g++ -Wall -std=c++11 source/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/sfml@2/lib
 #include <iostream>
 #include "../include/button.h"
 #include "../include/enemyclass.h"
 #include "../include/enemymovement.h"
 
 using std::cout;
 using std::endl;
 using std::string;
 
 int main()
 {
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
     
     sf::RenderWindow window(sf::VideoMode(800, 400), "Squirrels Tower Defense");
     Button rules("Rules",sf::Vector2f(200.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color::Green);
    //changed color of first button
    rules.setColorTextHover(sf::Color::Green);
    rules.setColorTextNormal(sf::Color(95,25,10));
    bool viewRules = 0;
    Button play("Play",sf::Vector2f(600.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color::Red);
    //Changed Color of Second Button
    play.setColorTextHover(sf::Color(95,25,10));
    play.setColorTextNormal(sf::Color::Green);
    bool playGame = 0;
    //extra button... Title????
    Button header("Squirrels Tower Defense", sf::Vector2f(400,50), sf::Vector2f(200,100), sf::Color::Black);
    header.setColorTextHover(sf::Color::Green);
 
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
             if (event.type == sf::Event::Closed)
                 window.close();
 
             if(event.type == sf::Event::MouseButtonPressed)
             
 
 
            rules.update(event, window);
            play.update(event, window);
            header.update(event, window);
        }
 
 
        window.clear();
        window.draw(rules);
        window.draw(play);
        window.draw(header);
        window.display();
    }
 
 
     return 0;
 
 }