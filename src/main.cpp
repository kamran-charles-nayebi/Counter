#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "interface.h"
#include "character.h"
#include "config.h"

static bool GameIsOver = false;
static int Level = 1;

int main()
{
    while (true)
    {
        
            // Loading the config file
            Config config;
            if(Level == 1)
            {
                config.SelectLevel("lvl/Level1.txt");
            }
            else if(Level == 2)
            {
                config.SelectLevel("lvl/Level2.txt");
            }
            else if(Level == 3)
            {
                config.SelectLevel("lvl/Level3.txt");
            }
            else if(Level == 4)
            {
                config.SelectLevel("lvl/Level4.txt");
            }
            else 
            {
                std::cout << "That's all for now, thanks for playing!" << std::endl;
                std::cin.get();
                return 0;
            }
            
            // Setting the characters' opponents
            config.First->SetOpponent(config.Second);
            config.Second->SetOpponent(config.First);
            if(config.Third != 0)
            {
                config.Third->SetOpponent(config.First);
            }
            // Seeding the random number generator with the time
            srand(time(0));
            while (GameIsOver == false)
            {
                //Checking for game over states
                if(config.Third != 0 && config.Third->Hp <= 0)
                {
                    delete config.Third;
                    config.Third = 0;
                    config.First->SetOpponent(config.Second);
                }
                if(config.Second != 0 && config.Second->Hp <= 0)
                {
                    delete config.Second;
                    config.Second = config.Third;
                    config.Third = 0;
                    config.First->SetOpponent(config.Second);
                }
                if (config.First->Hp <= 0 || (config.Second == 0 && config.Third == 0))
                {
                    GameIsOver = true;
                }
                // Skips over this part if the game is over
                if (!GameIsOver)
                {
                    system("clear");
                    // Updating the characters
                    config.First->Setup();
                    config.Second->Setup();
                    if(config.Third != 0)
                        config.Third->Setup();
                    // Displaying the menu and carrying out the actions
                    Interface::Print(config.First, config.Second, config.Third);
                    // Getting input from actors
                    config.First->Input();
                    config.Second->Input();
                    if(config.Third != 0)
                        config.Third->Input();
                }
            }
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            std::cout << "" << std::endl;
            // Displaying the correct game over message
            if (config.First->Hp <= 0)
            {
                std::cout << "You lose! ";
            }
            else {
                std::cout << "You win! ";
                Level++;
            }
            // Asking whether to close the program or to continue
            std::cout << "Do you want to continue?(y/n)" << std::endl;
            {
                char choice;
                std::cin >> choice;
                if (choice != 'y')
                {
                    return 0;
                }
            }
            GameIsOver = false;
        
    }
    return 0;
}