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
    // Starting currency and round 
    static int currency = 1;  
    static int round = 1;
    //Text for Displaying Currency
    sf::Text currencyText("Acorns: " + std::to_string(currency), font, 20);
    currencyText.setFillColor(sf::Color::White);
    currencyText.setPosition(10, 10);
    //Text for Displaying Round Number
    sf::Text roundText("Round: " + std::to_string(round), font, 20);
    roundText.setFillColor(sf::Color::White);
    roundText.setPosition(10, 40);
    //Object for SideBar Where You can Select Towers
    sf::RectangleShape sidebar(sf::Vector2f(800.f / 8.f, 400.f));
    sidebar.setPosition(800.f - (800.f / 8.f), 0);
    sidebar.setFillColor(sf::Color(80, 80, 80));
    // Texture for Map/Path
    sf::Texture mapTexture;
    mapTexture.loadFromFile("resources/final project image 2.0 cleaner.png");
    if (!mapTexture.loadFromFile("resources/final project image 2.0 cleaner.png")) 
    {
        cout << "Failed to load map texture" << endl;
        exit(1);
    }
    //Places the Texture onto a sprite that is mapped and scaled to the proper area.
    sf::Sprite mapSprite(mapTexture);
    mapSprite.setTextureRect(sf::IntRect(8, 685, 2564, 2152));
    mapSprite.setScale(700.f / 2564.f, 400.f / 2152.f);

 
    while(window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            //Closes Window When X is Pressed
            if (event.type == sf::Event::Closed)
                window.close();
 
            //Updates The Image of the button, used for the color change when hovering over it
            rulesButton.update(event, window);
            playButton.update(event, window);
 
            //Checks if the user clicks on either button in the main screen and moves them to the correct
            //Screen depending on what button they click on
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                //Grabs the positon of the window and uses it to get mouse postion for click position detection
                sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
                sf::Vector2f mousePos = window.mapPixelToCoords(pixelPos);
                //Detects if the player is on the title screen and if they clicked the rules button
                if (state == TITLE_SCREEN && rulesButton.getBounds().contains(mousePos)) 
                {
                    //Moves to Rules Screen
                    state = RULES_SCREEN;
                }
                //Detects if the player is on the title screen and if they clicked the play button
                else if (state == TITLE_SCREEN && playButton.getBounds().contains(mousePos)) 
                {
                    //Moves into the Game
                    state = GAME_SCREEN;
                }
                //Detects if the player is on the rules screen and if they clicked the back button
                else if (state == RULES_SCREEN && backButton.getBounds().contains(mousePos)) 
                {
                    //Moves back to the Title Screen
                    state = TITLE_SCREEN;
                }
            }
        }
 
        //Display Title Screen
        if (state == TITLE_SCREEN)
        {
            window.clear();
            window.draw(rulesButton);
            window.draw(playButton);
            window.draw(header);
            window.display();
        }
        //Display Rules Screen
        else if (state == RULES_SCREEN)
        {
            window.clear();
            window.draw(rulesTitle);
            window.draw(rulesText);
            window.draw(backButton);
            window.display();
        }
        //Display Game Screen
        else if (state == GAME_SCREEN)
        {
            window.clear();
            window.draw(mapSprite);
            currencyText.setString("Acorns: " + std::to_string(currency));
            roundText.setString("Round: " + std::to_string(round));
            window.draw(currencyText);
            window.draw(roundText);
            window.draw(sidebar);
            window.display();
        }
        
    }
    return 0;
}
