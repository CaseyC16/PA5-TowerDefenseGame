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
 #include "include/coneThrower.h"
 #include "include/archerSquirrel.h"
 #include "include/assaultSquirrel.h"
 #include "include/coinSpawn.h" // For Thad to have a coin in game
 #include "include/game.h" 

 
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

    //Set FPS
    window.setFramerateLimit(60);

    //Clock for Calculating Deltatime for consistant speed/fps
    sf::Clock frameClock;
    sf::Clock effectsTimer; //timer for visual animations
    float deltaTime = 0.0f;

    //Create Font and check if it loads properly
    sf::Font font;
    if (!font.loadFromFile("resources/college.ttf")) 
    {
        cout << "Could not load font" << endl;
        exit(1);
    }
    //Button on Title Screen for Rules
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
    string rulesTyped = "You Are A Squirrel.\n"
    "Fight Back Against the Humans trying to burn your forest!\n"
    "Earn Acorns by Slaying humans, and use them to\n" 
    "Purchase Special Squirrels to attack the humans.\n" 
    "Click the hire button for each squirrel you wish to purchase,\n"
    "then click on the tree youd like to place it on.\n"
    "Make sure you have enough funds!\n"
    "The Humans Arrive in waves that get larger as time passes.\n"
    "See how long you can last!";
    sf::Text rulesText(rulesTyped, font, 24);
    //Center the text vertically
    sf::FloatRect textRect = rulesText.getLocalBounds();
    rulesText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    rulesText.setPosition(400, 300);

    //Back button in Rules
    Button backButton("Back", {50, 20}, {100, 40}, sf::Color::Red);

    // Waypoints for Sprites to Walk to so they can loop around
    std::vector<sf::Vector2f> waypoints;
    //first Loop
    waypoints.push_back(sf::Vector2f(160.0f, 0.0f));  // spawn
    waypoints.push_back(sf::Vector2f(160.0f, 100.0f)); // upper 1
    waypoints.push_back(sf::Vector2f(160.0f, 315.0f)); // lower 1
    waypoints.push_back(sf::Vector2f(340.5f, 315.0f)); // lower 2
    waypoints.push_back(sf::Vector2f(340.0f, 100.0f)); // upper 2
    //second loop
    waypoints.push_back(sf::Vector2f(160.0f, 100.0f)); // upper 1
    waypoints.push_back(sf::Vector2f(160.0f, 315.0f)); // lower 1
    waypoints.push_back(sf::Vector2f(340.0f, 315.0f)); // lower 2
    waypoints.push_back(sf::Vector2f(670.0f, 315.0f)); // lower 3
    waypoints.push_back(sf::Vector2f(670.0f, 100.0f)); // upper 3
    waypoints.push_back(sf::Vector2f(340.0f, 100.0f)); // upper 2
    waypoints.push_back(sf::Vector2f(160.0f, 100.0f)); // upper 1
    //exit
    waypoints.push_back(sf::Vector2f(160.0f, 315.0f)); // lower 1
    waypoints.push_back(sf::Vector2f(340.5f, 315.0f)); // lower 2
    waypoints.push_back(sf::Vector2f(670.0f, 315.0f)); // lower 3
    waypoints.push_back(sf::Vector2f(670.0f, 400.0f)); // end  

    // Data For Round, Currency, Enemies, and Towers
    size_t spawnCount = 0;  //Amount of enemies Spawned
    sf::Clock enemySpawnTimer; //Interval Between enemy Spawns
    float spawnInterval = 1.0f; // Spawn an enemy every 1 second
    int currency = 100;  
    int round = 1;
    bool roundInProgress = false;
    Game game1;

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
    Button towerBtn1("Cone\n 100", {750.f, 100.f}, {100.f, 40.f}, sf::Color(54, 50, 168));
    Button towerBtn2("Archer\n  160", {750.f, 160.f}, {100.f, 40.f}, sf::Color(54, 50, 168));
    Button towerBtn3("Assault\n   400", {750.f, 220.f}, {100.f, 40.f}, sf::Color(54, 50, 168));
    Button roundStartButton("START", {750.f, 350.f}, {90.f, 60.f}, sf::Color::Green);
    roundStartButton.setColorTextNormal(sf::Color(95, 25, 10));

    //Text for Game Over Screen
    sf::Text gameOverHeader("GAME OVER...", font, 40);
    gameOverHeader.setFillColor(sf::Color::Red);
    gameOverHeader.setPosition(150, 100);
    sf::Text gameOverText("The Humans Burned Your Forest :o", font, 30);
    gameOverText.setFillColor(sf::Color(160,40,40));
    gameOverText.setPosition(150, 150);
    
    //Buttons for Game Over Screen
    Button retryButton("Retry?",sf::Vector2f(200.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    retryButton.setColorTextHover(sf::Color(160,40,40));
    retryButton.setColorTextNormal(sf::Color(54, 50, 168));
    Button menuButton("Menu",sf::Vector2f(600.f,300.f), sf::Vector2f(200.f, 71.f), sf::Color(50, 168, 82));
    menuButton.setColorTextHover(sf::Color(160,40,40));
    menuButton.setColorTextNormal(sf::Color(54, 50, 168));

    //variables for tower placement
    bool isPlacingTower1 = false;
    bool isPlacingTower2 = false;
    bool isPlacingTower3 = false;
    Tower *newTower = nullptr;
    std::vector<Coin> pineCoins;
    sf::Vector2f coinPos;
    Coin coinForKill;
    bool enemyKill = false;

    // Variables for enemy spawning
    size_t maxEnemiesThisRound = 0;
    
    // Define play area for bullet bounds checking
    sf::FloatRect playArea(0, 0, 700, 400);
    
    while(window.isOpen())
    {
        //Updates Deltatime for constant Speed
        deltaTime = frameClock.restart().asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            //Closes Window When X is Pressed
            if (event.type == sf::Event::Closed)
                window.close();
 
            //Updates The Image of the buttons, used for the color change when hovering over it
            rulesButton.update(event, window);
            playButton.update(event, window);
            towerBtn1.update(event, window);
            towerBtn2.update(event, window);
            towerBtn3.update(event, window);
            roundStartButton.update(event, window);
            retryButton.update(event, window);
            menuButton.update(event, window);
            backButton.update(event, window);
 
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
                    
                    // Reset game values when entering the game from title screen
                    round = 1;
                    currency = 100;
                    roundInProgress = false;
                    spawnCount = 0;
                    maxEnemiesThisRound = 0;
                    game1.clearEnemies();
                    game1.clearTowers();
                    game1.clearBullets();
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
                        //Moves into the Game
                        state = GAME_SCREEN;
                        
                        // Reset game values when entering the game from title screen
                        round = 1;
                        currency = 100;
                        roundInProgress = false;
                        spawnCount = 0;
                        maxEnemiesThisRound = 0;
                        game1.clearEnemies();
                        game1.clearTowers();
                        game1.clearBullets();
                    }
                    //Brings the player back to the title
                    else if (menuButton.getBounds().contains(mousePos))
                    {
                        state = TITLE_SCREEN;
                        game1.clearEnemies();
                        game1.clearTowers();
                        game1.clearBullets();
                    }
                }
                
                //Detects When A Button on the Game Screen in Clicked
                if (state == GAME_SCREEN) 
                {
                    // checks if the tower button is pressed and if you have enough currency
                    if(towerBtn1.getBounds().contains(mousePos) && currency >= 100)
                    {
                        // locks player in so that they can spawn a tower
                        isPlacingTower1 = true;
                        isPlacingTower2 = false;
                        isPlacingTower3 = false;
                        std::cout << "Selected Cone Tower for placement" << std::endl;
                    }
                    // checks if the tower button is pressed and if you have enough currency
                    else if (towerBtn2.getBounds().contains(mousePos) && currency >= 160)
                    {
                        // locks player in so that they can spawn a tower
                        isPlacingTower1 = false;
                        isPlacingTower2 = true;
                        isPlacingTower3 = false;
                        std::cout << "Selected Archer Tower for placement" << std::endl;
                    }
                    // checks if the tower button is pressed and if you have enough currency
                    else if (towerBtn3.getBounds().contains(mousePos) && currency >= 400)
                    {
                        // locks player in so that they can spawn a tower
                        isPlacingTower1 = false;
                        isPlacingTower2 = false;
                        isPlacingTower3 = true;
                        std::cout << "Selected Assault Tower for placement" << std::endl;
                    }
                    // checks if you are placing a tower
                    else if(isPlacingTower1 || isPlacingTower2 || isPlacingTower3)
                    {
                        // spawns in the cone tower
                        if(isPlacingTower1)
                        {
                            newTower = new ConeThrower(sf::Vector2f(mousePos));
                            if(newTower->placeTower(newTower, mousePos, game1, currency, sf::FloatRect(30.f,30.f,640.f,340.f)))
                            {
                                isPlacingTower1 = false;
                            }
                        }
                        // spawns in the archer tower
                        else if(isPlacingTower2)
                        {
                            newTower = new ArcherSquirrel(sf::Vector2f(mousePos));
                            if(newTower->placeTower(newTower, mousePos, game1, currency, sf::FloatRect(30.f,30.f,640.f,340.f)))
                            {
                                isPlacingTower2 = false;
                            }
                        }
                        // spawns in the assault tower
                        else if(isPlacingTower3)
                        {
                            newTower = new AssaultSquirrel(sf::Vector2f(mousePos));
                            if(newTower->placeTower(newTower, mousePos, game1, currency, sf::FloatRect(30.f,30.f,640.f,340.f)))
                            {
                                isPlacingTower3 = false;
                            }
                        }
                    }
                    
                    //Starts the Round as long as its not already started
                    if (roundStartButton.getBounds().contains(mousePos) && !roundInProgress)
                    {
                        roundInProgress = true;
                        spawnCount = 0;
                        //Spawns a specified number of enemies depending on the round number
                        maxEnemiesThisRound = 10 + round * 2;
                    }
                }
            }
        }
        
        // Update and process based on current state
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
            mapSprite.setScale(700.f / 2564.f, 400.f / 2152.f);
            window.draw(mapSprite);

            //moved up here cause i think it fits better here -Cameron
            sf::Vector2f coin1; // this is the coin for up in the left to show a coin for how many pinecoins we have -Thad
            coin1.x = 60; 
            coin1.y = 12;
            Coin currencyIndicatorCoin(coin1);

            // moved the tower drawing up here so its one of the first things to be drawn -Cameron
            for (int i = 0; i < game1.getNumOfTowers(); i++)
            {
                (game1.getTowers())[i]->draw(window);
            }

            // Enemy spawning logic
            if (roundInProgress && spawnCount < maxEnemiesThisRound)
            {
                //If the time between spawns is up, then spawn an enemy
                // had to change so much here :(
                if (enemySpawnTimer.getElapsedTime().asSeconds() >= spawnInterval)
                {
                    // changed so it doesnt spawn a peasant as the first enemy each time
                    Enemy *e = nullptr;
                    
                    //chaged to up the difficulty earlier
                    if(round <= 3)
                    { 
                        e = new Enemy(peasant);
                    }
                    //chaged to up the difficulty earlier
                    else if(round > 3 && round < 10)
                    {
                        if(spawnCount % 4 == 1)
                        {
                            e = new Enemy(knight);
                        }
                        else
                        {
                            e = new Enemy(peasant);
                        }
                    }
                    //final difficulty that goes on forever
                    else
                    {
                        if(spawnCount % 4 == 1)
                        {
                            e = new Enemy(heavyKnight);
                        }
                        else
                        {
                            e = new Enemy(knight);
                        }
                    }

                    // sets waypoints as long as there are enemies
                    if (e != nullptr)
                    {
                        e->getSprite().setPosition(waypoints[0]); //places enemy on first waypoint
                        e->setCurrentWaypoint(1); // routes to next waypoint
                        game1.addEnemy(e); // sends the Enemy to Game class
                        
                        spawnCount++;
                        enemySpawnTimer.restart();
                        std::cout << "Spawned enemy " << spawnCount << " of " << maxEnemiesThisRound << std::endl;
                    }
                }
            }

            // moved out of polling so that it proc during events
            game1.checkTowerRanges(deltaTime);
            std::vector<PineCone*> currentBullets = game1.getBullets();
            std::vector<PineCone*> activeBullets;
            std::vector<Enemy*> currentEnemies = game1.getEnemies();

            // this didnt belong in polling
            for(size_t i = 0; i < currentBullets.size(); ++i) 
            {
                PineCone* bullet = currentBullets[i];
                if (bullet == nullptr)
                {
                    continue;
                }

                bool bulletActive = true;
                
                //update bullet position
                bullet->update(deltaTime, currentEnemies);

                //draw bullet
                window.draw(bullet->getSprite());
                
                // checking if the bullet has gone out of the map
                if(bulletActive && bullet->outOfRange(playArea))
                {
                    delete bullet;
                    bulletActive = false;
                }
                
                // Keep track of active bullets
                if(bulletActive && !bullet->isMarked())
                {
                    activeBullets.push_back(bullet);
                }
            }
            
            //update active bullets
            //moved down here so it updates after it processes the bullets
            game1.updateBullets(activeBullets);

            // Process enemies and check for game end conditions
            bool allDead = true;
            bool enemyReachedEnd = false;
            
            // Create a temporary vector to track enemies that need to be removed
            std::vector<Enemy*> remainingEnemies;
            
            //updating enemy movement
            for (size_t i = 0; i < currentEnemies.size(); ++i)
            {
                Enemy* enemy = currentEnemies[i];
                if (enemy != nullptr)
                {
                    // Update enemy position along waypoints
                    enemy->updateMovement(waypoints, deltaTime);
                    enemy->drawSprite(window);
                    
                    // Check enemy state
                    if (enemy->getHealth() > 0)
                    {
                        allDead = false;
                        
                        // Check if enemy has reached end of path
                        if (enemy->getCurrentWaypoint() >= waypoints.size())
                        {
                            std::cout << "Enemy reached end of path!" << std::endl;
                            enemyReachedEnd = true;
                            
                            // Cleanup this enemy
                            delete enemy;
                            currentEnemies[i] = nullptr;
                            
                            // Game over condition
                            state = GAME_OVER_SCREEN;
                            break;
                        }
                        
                        // Keep this enemy in our tracking
                        remainingEnemies.push_back(enemy);
                    }
                    else
                    {
                        // Enemy died - spawn coin and award currency
                        currency += 5;
                        coinPos = enemy->getSprite().getPosition();
                        coinPos.y += 10; // Offset for visual effect
                        coinForKill.setPosition(coinPos);
                        enemyKill = true;
                        
                        // Clean up dead enemy
                        delete enemy;
                        currentEnemies[i] = nullptr;
                    }
                }
            }
            
            // updates enemies in the temp vector as long as the enemies have not reached the end
            if (!enemyReachedEnd) 
            {
                game1.updateEnemies(remainingEnemies);
            }
            
            static int coinflip=0; //need to make this transition slower, probably with a count so that it isnt too fast
            if (enemyKill&&coinflip%10==0)
            {
                coinForKill.setRotation(0);
            }
            else if(enemyKill&&coinflip%5==0)
            {
                coinForKill.setRotation(180);
            }
            if (enemyKill)
            {
                coinForKill.drawSprite(window);
            }

            coinflip++;

            if(coinflip>20)
            {
                enemyKill=false;
            }
            //coinForKill.drawSprite(window); // should be printing above not here -Thad

            //Ends the round and moves it forward after all enemies are defeated
            if (roundInProgress && allDead && spawnCount >= maxEnemiesThisRound && !enemyReachedEnd)
            {
                roundInProgress = false;
                round++;
                
                // Add currency for completing the round
                // might remove this for balance changes
                currency += 50 + (round * 3);
                
                // Clear enemies for the next round
                game1.clearEnemies();

                //remove any active bullets
                game1.clearBullets();
                
                // debugging thingy
                std::cout << "Round " << round-1 << " completed! Starting round: " << round << std::endl;
            }

            // brought this down here so that it can be the very last thing we render on the screen
            currencyText.setString("Coins:   " + std::to_string(currency));
            roundText.setString("Round: " + std::to_string(round));
            window.draw(currencyText);
            window.draw(roundText);
            window.draw(sidebar);
            window.draw(towerBtn1);
            window.draw(towerBtn2);
            window.draw(towerBtn3);
            window.draw(roundStartButton);
            currencyIndicatorCoin.drawSprite(window);
            
            window.display();
        }
        //Draws the Game over SCreen
        else if (state == GAME_OVER_SCREEN)
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