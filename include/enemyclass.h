#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

#define TEXTURE_LOADING_ERROR 2

#include <iostream>
#include <SFML/Graphics.hpp>
//make an enum for a debuff state and normal state
//enum state {normal, debuff};
//make an enum for if the enemy got killed by a tower 
//or gets destroyed by reaching the end of the path
//enum destroyed {tower, path}
//make an enum for enemy types
enum enemyType {peasant, knight, heavyKnight};

//when an enemy is hit with an attack, delete the instance of the enemy and make and enemy with a lower class
class Enemy
{
    public:
    //constructor for class to setdefault health and speed
    Enemy(enemyType type);

    //getter and setter functions
        //health
        int getHealth(){return mHealth;}
        void setHealth(int newhealth);

        //speed
        int getSpeed(){return mSpeed;}
        void setSpeed(int newspeed);

        //change type of enemy
        enemyType getType() const {return mType;}
        void setType(enemyType newType);

        //set enemy sprite when spawned
        const sf::Sprite & getSprite() const {return mSprite;}
        void setSprite(const std::string & sprite);
        void drawSprite(sf::RenderWindow & window);

    //other functions
    void targeted();

    //destructor
    ~Enemy(); //every time an enemy is destroyed, make player earn currency

    private:
    int mHealth;
    int mSpeed;
    sf::Sprite mSprite;
    sf::Texture mTexture;
    enemyType mType;

};

#endif //guard code