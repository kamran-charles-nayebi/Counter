#ifndef CONFIG_H
#define CONFIG_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "character.h"
#include "interface.h"

class Config
{
private:
    int position;
    std::string FilePath;
public:
    Character* First;
    Character* Second;
    Character* Third;
private:
    void LoadMenu() const;
    void LoadCharacter(Character* person);
    void ModConfig(std::string toReplace, std::string toReplaceWith) const;
public:
    Config();
    ~Config();
    void SelectLevel(std::string aFilePath);
};
#endif