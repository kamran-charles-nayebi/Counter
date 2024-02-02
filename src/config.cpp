#include "config.h"

config::config(std::string FilePath)
    : First(0), Second(0)
{
    // Opening the file
    std::ifstream fin(FilePath);
    std::string line;
    // Streaming the data into a variable line by line
    while (getline(fin, line)) {
        // Removes everything but the variable
        std::istringstream sin(line.substr(line.find("=") + 1));
        if (line.find("Story") != -1)
        {
            // Creates the interface and loads it
            Interface* menu = new Interface();
            Menu = menu;
            position = fin.tellg();
            LoadMenu(FilePath, menu);
        }
        else if (line.find("Character") != -1)
        {
            // Creates the characters and loads them
            if(First == 0)
            {
                Character* first = new Character();
                First = first;
                position = fin.tellg();
                LoadCharacter(FilePath, first);
            }
            else if(Second == 0)
            {
                Character* second = new Character();
                Second = second;
                position = fin.tellg();
                LoadCharacter(FilePath, second);
            }
        }
    }
}

void config::LoadMenu(std::string FilePath, Interface* menu)
{
    std::ifstream fin(FilePath);
    fin.seekg(position);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream sin(line.substr(line.find(":") + 1));
        if (line.find("Cutscene") != -1)
            getline(sin, menu->story);
    }
}

void config::LoadCharacter(std::string FilePath, Character* person) {
    std::ifstream fin(FilePath);
    fin.seekg(position);
    std::string line;
    bool loop = true;
    // Finds the variables in the file and pushes their value into the corresponding variable
    while (getline(fin, line) && loop == true) {
        std::istringstream sin(line.substr(line.find("=") + 1));
        if (line.find("Name") != -1 && person->Name == "Default")
            sin >> person->Name;
        else if (line.find("isPlayer") != -1)
            sin >> person->isPlayer;
        else if (line.find("Action") != -1)
            sin >> person->Action;
        else if (line.find("isProne") != -1)
            sin >> person->isProne;
        else if (line.find("Hp") != -1)
            sin >> person->Hp;
        else if (line.find("Damage") != -1)
            sin >> person->Damage;
        else if (line.find("isStunned") != -1)
            sin >> person->isStunned;
        else if (line.find("ActionName") != -1)
            sin >> person->ActionName;
        else if (line.find("Limit") != -1)
            sin >> person->Limit;
        else if (line.find("Speed") != -1)
        {
            sin >> person->Speed;
            loop = false;
        }
    }
}