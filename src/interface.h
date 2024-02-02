#ifndef INTERFACE_H
#define INTERFACE_H
#include "character.h"

class Interface
{
    static void Info(const Character* aPerson);
public:
    static void Cutscene(const std::string story);
    static bool Rules(const bool rules);
    static void Print(Character* First, Character* Second, Character* Third);
    static void MenuUpdate(Character* aPlayer);
};
#endif