#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "character.h"
#include "interface.h"

class config
{
private:
    int position;
public:
    Interface* Menu;
    Character* First;
    Character* Second;
private:
    void LoadMenu(std::string FilePath, Interface* menu);
    void LoadCharacter(std::string FilePath, Character* person);
public:
    config(std::string FilePath);
};
#endif