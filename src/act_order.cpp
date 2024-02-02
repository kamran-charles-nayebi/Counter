#include "act_order.h"

void ActOrder::Act(Character* Actor1, Character* Actor2)
{
    // Checking whether they act or not
    if (Actor1->isProne == true && Actor2->isProne == true)
    {
        std::cout << "You stare at each other, dazed, and stand up" << std::endl;
        Actor1->isProne = false;
        Actor2->isProne = false;
    }
    else
    {
        // Checks who acts first
        if(Actor1->Speed > Actor2->Speed)
        {
            Action(Actor1);
            Action(Actor2);
        }
        else
        {
            Action(Actor2);
            Action(Actor1);
        }
    }
}
void ActOrder::Action(Character* Actor)
{
    // Assigning the input to the character's actions
    switch(Actor->Action)
    {
        case ATTACK:
        Actor->Attack();
        break;
        case DEFEND:
        Actor->Defend();
        break;
        case GRAPPLE:
        Actor->Grapple();
        break;
        case PARRY:
        Actor->Parry();
        break;
        // If the character is stunned, do nothing
        default:
        break;
    }
}