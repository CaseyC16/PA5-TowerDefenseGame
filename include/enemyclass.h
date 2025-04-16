#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

//make an enum for a debuff state and normal state
//enum state {normal, debuff};

//when an enemy is hit with an attack, delete the instance of the enemy and make and enemy with a lower class
class Enemy
{
    public:
    //constructor for class to set health and speed
    Enemy();

    int getHealth(){return mHealth;};
    void setHealth(int health);
    int getSpeed(){return mSpeed;};
    void setspeed(int speed);

    ~Enemy(); //every time an enemy is destroyed, make player earn currency

    protected:
    int mHealth;
    int mSpeed;

};

class Peasant : public Enemy 
{
    public:

    private:
        
};

#endif //guard code