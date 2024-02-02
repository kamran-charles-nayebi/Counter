#include "config.h"

Config::Config()
    : First(0), Second(0), Third(0), position(0)
{
    // Initializing the pointers to diverse objects
}

void Config::SelectLevel(std::string aFilePath)
{
    FilePath = aFilePath;
    // Opening the file
    std::ifstream fin(FilePath);
    std::string line;
    // Streaming the data into a variable line by line
    while (getline(fin, line)) {
        if (line.find("Story") != -1)
        {
            // Creates the interface and loads it
            position = fin.tellg();
            LoadMenu();
        }
        else if (line.find("Character") != -1)
        {
            // Creates the characters and loads them
            if(First == 0)
            {
                Character* first = new Character();
                First = first;
                position = fin.tellg();
                LoadCharacter(first);
            }
            else if(Second == 0)
            {
                Character* second = new Character();
                Second = second;
                position = fin.tellg();
                LoadCharacter(second);
            }
            else if(Third == 0)
            {
                Character* third = new Character();
                Third = third;
                position = fin.tellg();
                LoadCharacter(third);
            }
        }
    }
}

Config::~Config()
{
    // Freeing up the memory
    delete First;
    delete Second;
    if(Third != 0)
    {
        delete Third;
    }
}

void Config::LoadMenu() const
{
    // Loads the cutscene 
    std::ifstream fin(FilePath);
    fin.seekg(position);
    std::string line;
    while (getline(fin, line)) {
        std::istringstream sin(line.substr(line.find("=") + 1));
        if (line.find("Cutscene") != -1)
        {
            std::string temp;
            getline(sin, temp);
            Interface::Cutscene(temp);
        }
        else if (line.find("Rules") != -1)
        {
            // Stores whether the player wants to hear the rules or not
            bool temp;
            sin >> temp;
            if(!Interface::Rules(temp))
            {
                ModConfig("Rules = 1", "Rules = 0");
            }
        }
    }
}

void Config::LoadCharacter(Character* person) 
{
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

void Config::ModConfig(std::string toReplace, std::string toReplaceWith) const
{
    std::ifstream fin(FilePath);
    std::string line;
    // Creates a temp file to write the modified text to
    std::ofstream fout("lvl/temp.txt");
    while (getline(fin, line)) {
        if (line.find(toReplace) != -1)
        {
            line = toReplaceWith;
        }
        fout << line << std::endl;
    }
    // Renames the modified file to the original file, overwritting it
    std::rename("lvl/temp.txt", FilePath.c_str());
}