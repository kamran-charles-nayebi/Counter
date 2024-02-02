#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>

#define ATTACK 1
#define DEFEND 2
#define GRAPPLE 3
#define PARRY 4
#define STRUGGLE 5
#define REINFORCE 6

#define NORMAL 0
#define WEAK 1
#define NOTHING 2
#define COUNTERED 10

class Character
{
public:
    Character* OpponentID;
    std::string ActionName;
    std::string Name;
    std::string Status;
    int Action;
    int Damage;
    int Hp;
    int Limit;
    int Speed;
    bool isPlayer;
    bool isProne;
    bool isStunned;

private:
    float EnemyAttacked;
    float EnemyDefended;
    float EnemyGrappled;
    float EnemyParried;

public:
    Character();
    void SetOpponent(Character* aOpponent);
    void Print();
    void Setup();
    void Input();
    void AI();

    void Attack();
    void Defend();
    void Grapple();
    void Parry();

};
#endif