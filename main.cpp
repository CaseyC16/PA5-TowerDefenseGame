/**
 * @file main.cpp
 * @author Casey Cook, Cameron Bauman, Thad Selby, Joseph Moran
 * @brief Balloon Tower Defense Game
 * @date 2025-04-09
 */

 //COMPILE g++ -Wall main.cpp source/*.cpp -o sfml-app -lsfml-graphics -lsfml-window -lsfml-system
 //On Mac: g++ -Wall -std=c++11 main.cpp source/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -I/opt/homebrew/opt/sfml@2/include -L/opt/homebrew/opt/sfml@2/lib
 #include <iostream>
 #include <vector>
 #include "include/button.h"
 #include "include/enemyclass.h"
 #include "include/enemymovement.h"
 #include "include/coneThrower.h"
 #include "include/archerSquirrel.h"
 #include "include/assaultSquirrel.h"
 
 using std::cout;
 using std::endl;
 using std::string;
 
 int main()
 {
    enum Screen {TITLE_SCREEN, RULES_SCREEN, GAME_SCREEN, GAME_OVER_SCREEN};
    //set default state
    Screen state = TITLE_SCREEN;
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
    Button backButton("Back", {50, 20}, {100, 40}, sf::Color::Red);
    // Data For Round, Currency, Enemies, and Towers
    static int currency = 1;  
    static int round = 1;
    bool roundInProgress = false;
    std::vector<Enemy*> currentEnemies;
    std::vector<Tower*> placedTowers;
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
    sidebar.setFillColor(sf::Color(95, 25, 10));
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
    //Buttons for the Towers & Round Start Button
    Button towerBtn1("1", {750.f, 100.f}, {40.f, 40.f}, sf::Color(54, 50, 168));
    Button towerBtn2("2", {750.f, 160.f}, {40.f, 40.f}, sf::Color(54, 50, 168));
    Button towerBtn3("3", {750.f, 220.f}, {40.f, 40.f}, sf::Color(54, 50, 168));
    Button roundStartButton("START", {750.f, 350.f}, {90.f, 60.f}, sf::Color::Green);
    roundStartButton.setColorTextNormal(sf::Color(95, 25, 10));
    //Text for Game Over Screen
    sf::Text gameOverHeader("GAME OVER...", font, 40);
    gameOverHeader.setFillColor(sf::Color::Red);
    gameOverHeader.setPosition(150, 100);
    sf::Text gameOverText("The Humans Burned Your Forest :(", font, 30);
    gameOverText.setFillColor(sf::Color(160,40,40));
    gameOverText.setPosition(150, 115);
    //Buttons for Game Over Screen
    Button retryButton("Retry?",sf::Vector2f(200.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    retryButton.setColorTextHover(sf::Color(160,40,40));
    retryButton.setColorTextNormal(sf::Color(54, 50, 168));
    Button menuButton("Menu",sf::Vector2f(600.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    menuButton.setColorTextHover(sf::Color(160,40,40));
    menuButton.setColorTextNormal(sf::Color(54, 50, 168));


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
            towerBtn1.update(event, window);
            towerBtn2.update(event, window);
            towerBtn3.update(event, window);
            roundStartButton.update(event, window);
            retryButton.update(event, window);
            menuButton.update(event, window);
 
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
                //Responds Depending on What Button Player Presses On Game over Screen
                if (state == GAME_OVER_SCREEN)
                {
                    //Resets the Round and Currency and enemies, while bringing the player back into the game loop
                    if (retryButton.getBounds().contains(mousePos))
                    {
                        round = 1;
                        currency = 1;
                        state = GAME_SCREEN;
                        currentEnemies.clear();
                    }
                    //Brings the player back to the menu
                    else if (menuButton.getBounds().contains(mousePos))
                    {
                        state = TITLE_SCREEN;
                        currentEnemies.clear();
                    }
                }
                //Detects When A Button on the Game Screen in Clicked
                if (state == GAME_SCREEN) 
                {
                    
                    if(towerBtn1.getBounds().contains(mousePos)) // && currency >= 1 (check if player has enough money)
                    {
                        //Needs to Allow Player to Spawn and Place the Tower
                        //Placeholder for now
                        cout << "Tower 1 button clicked!" << endl;
                        Tower *a = new ConeThrower(sf::Vector2f(100.f,100.f));
                        placedTowers.push_back(a);
                    }
                    if (towerBtn2.getBounds().contains(mousePos)) // && currency >= 2 (check if player has enough money)
                    {
                        //Needs to Allow Player to Spawn and Place the Tower
                        //Placeholder for now
                        cout << "Tower 2 button clicked!" << endl;
                        Tower *b = new ArcherSquirrel(sf::Vector2f(100.f,175.f));
                        placedTowers.push_back(b);
                    }
                    if (towerBtn3.getBounds().contains(mousePos)) // && currency >= 3 (check if player has enough money)
                    {
                        //Needs to Allow Player to Spawn and Place the Tower
                        //Placeholder for now                        
                        cout << "Tower 3 button clicked!" << endl;
                        Tower *c = new AssaultSquirrel(sf::Vector2f(100.f,250.f));
                        placedTowers.push_back(c);
                    }
                    //Starts the Round as long as its not already started
                    if (roundStartButton.getBounds().contains(mousePos) && !roundInProgress)
                    {
                        roundInProgress = true;
                        //Spawns a specified number of enemies depending on the round number using a vector
                        for (int i = 0; i < 10 + round * 2; ++i)
                        {
                            Enemy * e = new Enemy(peasant);
                            currentEnemies.push_back(e);
                        }
                    }
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

            mapSprite.setScale(700.f / 2564.f, 400.f / 2152.f);
            window.draw(mapSprite);

            currencyText.setString("Acorns: " + std::to_string(currency));
            roundText.setString("Round: " + std::to_string(round));
            window.draw(currencyText);
            window.draw(roundText);

            window.draw(sidebar);
            window.draw(towerBtn1);
            window.draw(towerBtn2);
            window.draw(towerBtn3);
            window.draw(roundStartButton);

            //Assumes all enemies are dead unless the check below states otherwise
            bool allDead = true;
            //Iterates through every enemy spawned
            for (size_t i = 0; i < currentEnemies.size(); ++i)
            {
                //if there is still an enemy in the vector
                if (currentEnemies[i])
                {
                    //Draw the enemy
                    currentEnemies[i]->drawSprite(window);
                    //Checks if the enemy is alive
                    if (1) //Add the way to check if the enemy is alive as a condition when implimented
                    {
                        allDead = false;
                    }
                }
            }

            //draw any placed towers
            for (size_t i = 0; i < placedTowers.size(); i++)
            {
                placedTowers[i]->draw(window);
            }

            //Ends the round and moves it forward after all enemies are defeated
            if (roundInProgress && allDead)
            {
                roundInProgress = false;
                round++;

                // Frees the memory for each enemy spawned at the beginning of the round
               for (size_t i = 0; i < currentEnemies.size(); ++i)
               {
                   delete currentEnemies[i];
               }

                currentEnemies.clear();
            }

            window.display();
        }
        else if(state == GAME_OVER_SCREEN)
        {
            window.clear();

            window.draw(gameOverHeader);
            window.draw(gameOverText);

            window.draw(retryButton);
            window.draw(menuButton);

            window.display();
        }
        
    }

    return 0;
}