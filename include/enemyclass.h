#ifndef ENEMYCLASS_H
#define ENEMYCLASS_H

//make an enum for a debuff state and normal state
//enum state {normal, debuff};
//make an enum for if the enemy got killed by a tower 
//or gets destroyed by reaching the end of the path
//enum destroyed {tower, path}

//when an enemy is hit with an attack, delete the instance of the enemy and make and enemy with a lower class
class Enemy
{
    public:
    //constructor for class to setdefault health and speed
    Enemy();
    Enemy(int h);

    int getHealth(){return mHealth;};
    void setHealth(int health) {mHealth = health;}
    int getSpeed(){return mSpeed;};
    void setspeed(int speed);

    ~Enemy() {} //every time an enemy is destroyed, make player earn currency

    private:
    int mHealth;
    int mSpeed;

};

#endif //guard code