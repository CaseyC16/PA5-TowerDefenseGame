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
 
 using std::cout;
 using std::endl;
 using std::string;
 
 int main()
 {
     enum Screen {TITLE_SCREEN, RULES_SCREEN, GAME_SCREEN};
 
     //set default state
     Screen state = TITLE_SCREEN;
 
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
     
    //Create Game Window
    sf::RenderWindow window(sf::VideoMode(800, 400), "Squirrels Tower Defense");
    //Create Font and check if it loads properly
    sf::Font font;
    if (!font.loadFromFile("resources/college.ttf")) 
    {
        cout << "Could not load font" << endl;
        exit(1);
    }
    Button rulesButton("Rules",sf::Vector2f(200.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    //changed color of first button
    rulesButton.setColorTextHover(sf::Color(160,40,40));
    rulesButton.setColorTextNormal(sf::Color(54, 50, 168));
    Button playButton("Play",sf::Vector2f(600.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    //Changed Color of Second Button
    playButton.setColorTextHover(sf::Color(160,40,40));
    playButton.setColorTextNormal(sf::Color(54, 50, 168));
    //Title Text
    sf::Text header("SQUIRRELS TOWER DEFENSE", font, 40);
    header.setFillColor(sf::Color(95, 25, 10));
    header.setPosition(150, 50);
     
    //Rules Title and Text for when Button is pressed
    sf::Text rulesTitle("RULES", font, 40);
    rulesTitle.setPosition(330, 20);
    sf::Text rulesText("Placeholder text for how to play...", font, 24);
    //Center the text vertically
    sf::FloatRect textRect = rulesText.getLocalBounds();
    rulesText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    rulesText.setPosition(400, 300);
    //Back button in Rules
    Button backButton("Back", {20, 20}, {100, 40}, sf::Color::Red);
 
 
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
 
 
            rulesButton.update(event, window);
            playButton.update(event, window);
 
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                if (state == TITLE_SCREEN && rulesButton.getDimensions().x > 0) 
                {
                    if (rulesButton.getBounds().contains(mousePos))
                    {
                        state = RULES_SCREEN;
                    }
                }
                if (state == TITLE_SCREEN && playButton.getDimensions().x > 0) 
                {
                    if (playButton.getBounds().contains(mousePos))
                    {
                        state = GAME_SCREEN;
                    }
                }
                else if (state == RULES_SCREEN && backButton.getDimensions().x > 0) 
                {
                    if (backButton.getBounds().contains(mousePos))
                    {
                        state = TITLE_SCREEN;
                    }
                }
            }
        }
 
        if (state == TITLE_SCREEN)
        {
            window.clear();
            window.draw(rulesButton);
            window.draw(playButton);
            window.draw(header);
            window.display();
        }
        else if (state == RULES_SCREEN)
        {
            window.clear();
            window.draw(rulesTitle);
            window.draw(rulesText);
            window.draw(backButton);
            window.display();
        }
        else if (state == GAME_SCREEN)
        {
            window.clear();
            // Temporary game screen view
            window.display();
        }
        
    }
    return 0;
}
