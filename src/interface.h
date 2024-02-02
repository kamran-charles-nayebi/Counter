#ifndef INTERFACE_H
#define INTERFACE_H
#include "character.h"
#include "act_order.h"

class Interface
{
public:
    std::string story;
private:
    void Info(Character* aPlayer);
public:
    void Cutscene();
    void Rules();
    void Print(Character* aPlayer);
};
#endif