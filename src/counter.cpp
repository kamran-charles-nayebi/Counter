#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>

#include "interface.h"
#include "character.h"
#include "config.h"

bool GameIsOver = false;
bool GameExit = false;

int main()
{
    while (GameExit == false)
    {
        // Loading the config file
        config Config("config.txt");
        Config.Menu->Rules();
        Config.Menu->Cutscene();
        // Setting the characters' opponents
        Config.First->SetOpponent(Config.Second);
        Config.Second->SetOpponent(Config.First);
        // Seeding the random number generator with the time
        srand(time(0));
        while (GameIsOver == false)
        {
            //Checking for game over states
            if (Config.First->Hp <= 0 || Config.Second->Hp <= 0)
            {
                GameIsOver = true;
            }
            // Skips over this part if the game is over
            if (!GameIsOver)
            {
                // Updating the characters
                Config.First->Setup();
                Config.Second->Setup();
                // Displaying the menu and carrying out the actions
                Config.Menu->Print(Config.First);
                // Getting input from the player
                Config.First->Input();
                // Getting input from the enemy
                Config.Second->AI();
            }
        }
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
        // Displaying the correct game over message
        if (Config.First->Hp <= 0)
        {
            std::cout << "You lose! ";
        }
        else {
            std::cout << "You win! ";
        }
        // Asking whether to close the program or to continue
        std::cout << "Do you want to continue?(y/n)" << std::endl;
        {
            char choice;
            std::cin >> choice;
            if (choice != 'y')
            {
                GameExit = true;
            }
        }
        GameIsOver = false;
        delete (Config.First);
        delete (Config.Second);
    }
    return 0;
}