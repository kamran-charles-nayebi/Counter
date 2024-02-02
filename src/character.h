#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>

#define ATTACK 1
#define DEFEND 2
#define GRAPPLE 3
#define PARRY 4
#define STANDUP 5

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
    int Cooldown;
    int Damage;
    int Hp;
    int Limit;
    int Speed;
    bool isPlayer;
    bool isProne;
    bool isStunned;

private:
    float PlayerAttacked;
    float PlayerDefended;
    float PlayerGrappled;
    float PlayerParried;

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
    void StandUp();

};
#endif