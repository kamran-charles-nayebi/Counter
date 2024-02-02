#include "interface.h"

void Interface::Info(Character* aPerson)
{
    {
        if (aPerson->isProne == true)
        {
            aPerson->Status = "Prone";
        }
        else
        {
            aPerson->Status = "Default";
        }
        std::cout << aPerson->Name << std::endl;
        std::cout << "Action: " << aPerson->ActionName << std::endl;
        std::cout << "Status: " << aPerson->Status << std::endl;
        std::cout << "Health: " << aPerson->Hp << std::endl;
    }
}
void Interface::Cutscene()
{
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    std::cout << story << std::endl;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
}
void Interface::Print(Character* aPlayer)
{
    ActOrder Order;
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    // Making the characters act out their actions
    Order.Act(aPlayer->OpponentID, aPlayer);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    // Printing information about each character
    Info(aPlayer->OpponentID);
    std::cout << "" << std::endl;
    std::cout << "" << std::endl;
    Info(aPlayer);
    std::cout << "1.Attack 2.Defend 3.Grapple 4.Parry" << std::endl;
    std::cout << "Enter an action to continue" << std::endl;
}
void Interface::Rules()
{
    // Displaying the rules if the player wants
    std::cout << "Do you want to hear the rules?(y/n)" << std::endl;
    if (std::cin.get() == 'y')
    {
        std::cout << "The goal of the game is to counter your opponent" << std::endl;
        std::cout << "Attack -> Defend -> Grapple -> Parry -> Attack" << std::endl;
        std::cout << "Defend -> Reinforce  Grapple -> Struggle" << std::endl;
        std::cout << "When you successfully counter with Defend, Grapple, or Parry and you have rope, you can tie your enemy up" << std::endl;
        std::cout << "Every two turns, one of you picks up a rope" << std::endl;
        std::cout << "Tying the arms makes it impossible to have a rope and it halves the damage" << std::endl;
        std::cout << "Tying the legs up makes it impossible to stand up or to tie someone up" << std::endl;
        std::cout << "When prone, the effectiveness of your actions is lowered by one, from normal to weak to nothing" << std::endl;
        std::cout << "Two Attacks or two Grapples at the same time are weakened" << std::endl;
        std::cout << "Reinforcing a bond makes it impossible to escape from" << std::endl;
        std::cout << "To win the game, tie up your opponent's arms and legs or drop them to 0 hp " << std::endl;
        std::cout << "" << std::endl;
    }
}