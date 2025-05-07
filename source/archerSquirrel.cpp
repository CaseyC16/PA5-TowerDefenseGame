#include "../include/archerSquirrel.h"
#include "../include/game.h"

ArcherSquirrel::ArcherSquirrel(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/archerSquirrel.png"))
    {
        std::cout<<"Error opening file\n";
        exit(1);
    }
    mSprite.setTexture(mTexture);
    sf::Vector2u textureSize = mTexture.getSize();
    float scaleX = 60.0f / textureSize.x;
    float scaleY = 60.0f / textureSize.y;
    mSprite.setScale(sf::Vector2f(scaleX, scaleY));

    //set origin to center
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(sf::Vector2f(bounds.width / 2.f, bounds.height / 2.f));
    mRadius = 30;
    mPos = position;
    mFireRate = 10; //sleep 10 seconds between attacks
    //mDamage = 10; //take 1 hp from first 10 enemies
    mSprite.setPosition(mPos);
    mCost = 80;
}

void ArcherSquirrel::attack(std::queue<Enemy> &q)
{
    //take one hp from all enemies
    while(!q.empty())
    {
        Enemy temp = q.front(); //save enemy in case it is destroyed by attack
        // int health = temp.getHealth();
        q.pop(); //remove enemy from queue
        temp.targeted(); //shoot at enemy
    }
}

bool ArcherSquirrel::placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds)
{
    //Check if position is on the map
    if(!checkBounds(position, mapBounds, currentGame.getTowers()))
    {
        std::cout << "Invalid placement - click again on a valid location to place tower." << std::endl;
        return false;
    }

    //Check if player has enough currency
    if(currency < 80)
    {
        std::cout << "Not enough currency to place tower." << std::endl;
        return false;
    }

    Tower *newTower = new ArcherSquirrel(sf::Vector2f(position));
    std::cout << "Placed Archer Squirrel at x = " << position.x << ", y = " << position.y << std::endl;
    currentGame.addTower(newTower);
    currency -= 80;
    return true;
}