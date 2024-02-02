#include "character.h"
#include "act_order.h"
#include "interface.h"

void Interface::Info(const Character *aPerson)
{
    {
        // Printing the information about them
        std::cout << aPerson->Name << std::endl;
        std::cout << "Action: " << aPerson->ActionName << std::endl;
        std::cout << "Status: " << aPerson->Status << std::endl;
        std::cout << "Health: " << aPerson->Hp << std::endl;
    }
}
void Interface::Cutscene(const std::string story)
{
    // Displaying intro screen only once by taking advantage of a bug
    system("clear");
    std::cout << "Welcome to Counter! A Game where you counter your opponents to win" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press enter to play" << std::endl;
    std::cin.get();
    system("clear");
    // Displaying the cutscene
    std::cout << story << std::endl;
    std::cout << "" << std::endl;
    std::cout << "Press enter to continue" << std::endl;
    std::cin.get();
}
bool Interface::Rules(const bool rules)
{
    // Checks if it should display the rules
    if (rules == false)
    {
        return true;
    }
    // Displaying the rules if the player wants
    std::cout << "Do you want to hear the rules?(y/n)" << std::endl;
    if (std::cin.get() == 'y')
    {
        system("clear");
        std::cout << "The goal of the game is to counter your opponent" << std::endl;
        std::cout << "Attack -> Defend -> Grapple -> Parry -> Attack" << std::endl;
        std::cout << "When you successfully counter with Defend, Grapple, or Parry, the enemy is stunned for a turn" << std::endl;
        std::cout << "When prone, the effectiveness of your actions is lowered by one, from normal to weak to nothing" << std::endl;
        std::cout << "Two Attacks or two Grapples at the same time are weakened" << std::endl;
        std::cout << "To win the game, drop the enemy's hit points to 0 hp " << std::endl;
        std::cout << "" << std::endl;
        std::cout << "Press enter to continue" << std::endl;
        std::cin.ignore(100, '\n');
        std::cin.get();
        return true;
    }
    else
    {
        // If they don't, remembers it
        return false;
    }
}
void Interface::Print(Character *First, Character *Second, Character *Third)
{
    // Making the characters act out their actions
    ActOrder::Act(First, Second, Third);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    // Printing information about each character
    if (Third != 0)
    {
        Interface::Info(Third);
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
    }
    if (Second != 0)
    {
        Interface::Info(Second);
        std::cout << "" << std::endl;
        std::cout << "" << std::endl;
    }
    Interface::Info(First);
    if (Third != 0 && Second != 0)
    {
        int temp;
        std::cout << "Select opponent(" << Third->Name << "(1), " << Second->Name << "(2))" << std::endl;
        std::cin.ignore(100, '\n');
        std::cin >> temp;
        if (temp == 1)
            First->SetOpponent(Third);
        else
            First->SetOpponent(Second);
    }
    // Printing the possible choices for the player
    std::cout << "1.Attack 2.Defend 3.Grapple 4.Parry ";
    Interface::MenuUpdate(First);
    std::cout << "" << std::endl;
    std::cout << "Enter an action to continue" << std::endl;
}
void Interface::MenuUpdate(Character *aPlayer)
{
    // Updating the possible choices for the player
    if (aPlayer->isProne == true)
    {
        aPlayer->Limit++;
        std::cout << aPlayer->Limit << ".Stand up";
    }
}
