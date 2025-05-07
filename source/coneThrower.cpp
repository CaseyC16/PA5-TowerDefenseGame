#include "../include/coneThrower.h"
#include "../include/game.h"


ConeThrower::ConeThrower(sf::Vector2f position)
{
    //load texture
    if(!mTexture.loadFromFile("resources/coneSquirrel.png"))
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
    mRadius = 100;
    mPos = position;
    mFireRate = 1; //sleep one second between attacks
    //mDamage = 1; //take one hp from enemy
    mSprite.setPosition(mPos);
    mCost = 50;
}

void ConeThrower::attack(std::queue<Enemy> &q)
{
    //take one hp from first enemy in queue
    //can call Enemy targeted function instead of manually removing health
    Enemy temp = q.front();
    // int health = temp.getHealth();
    q.pop(); //remove enemy from queue
    temp.targeted(); //shoot at enemy
}

bool ConeThrower::placeTower(Tower *tower, sf::Vector2f position, Game &currentGame, int &currency, sf::FloatRect mapBounds)
{
    //Check if position is on the map
    if(!checkBounds(position, mapBounds, currentGame.getTowers()))
    {
        std::cout << "Invalid placement - click again on a valid location to place tower." << std::endl;
        return false;
    }

    //Check if player has enough currency
    if(currency < 50)
    {
        std::cout << "Not enough currency to place tower." << std::endl;
        return false;
    }

    Tower *newTower = new ConeThrower(sf::Vector2f(position));
    std::cout << "Placed ConeThrower at x = " << position.x << ", y = " << position.y << std::endl;
    currentGame.addTower(newTower);
    currency -= 50;
    return true;
}