#include "character.h"
#include "matcher.h"

Character::Character()
    :Name("Default"), isPlayer(false), Action(0), isProne(false), Hp(200), Damage(40), isStunned(false), 
    ActionName("Idle"), Limit(4), EnemyAttacked(0), EnemyDefended(0), EnemyGrappled(0), EnemyParried(0)
{}
void Character::Setup()
{
    // Making it so stunned characters don't take their turn
    if (isStunned == true)
    {
        isStunned = false;
        ActionName = "Stunned";
        Action = 0;
    }
    // Making the prone characters stand up
    if (isProne == true)
    {
        std::cout << Name << " stands up " << std::endl;
        isProne = false;
    }
}
void Character::Input()
{
    // Taking in the player's inputs and filtering out the incorrect ones
    while (!(std::cin >> Action) || Action > Limit)
    {
        std::cout << "Wrong input, please enter a correct action" << std::endl;
        std::cin.clear();
        std::cin.ignore(100, '\n');
    }
}
void Character::AI()
{
    // Playing normally
    Action = rand() % 4 + 1;
    // Will try to counter player if an action is used too much
    if (EnemyAttacked > 0)
    {
        if (EnemyAttacked >= 2)
        {
            Action = PARRY;
            EnemyAttacked--;        }

        EnemyAttacked -= 0.25f;
    }
    if (EnemyDefended > 0)
    {
        if (EnemyDefended >= 2)
        {
            Action = ATTACK;
            EnemyDefended--;
        }
        EnemyDefended -= 0.25f;
    }
    if (EnemyGrappled > 0)
    {
        if (EnemyGrappled >= 2)
        {
            Action = DEFEND;
            EnemyGrappled--;
        }
        EnemyGrappled -= 0.25f;
    }
    if (EnemyParried > 0)
    {
        if (EnemyParried >= 2)
        {
            Action = GRAPPLE;
            EnemyParried--;
        }
        EnemyParried -= 0.25f;
    }
    // Stores player's actions so it can counter them
    switch (OpponentID->Action)
    {
    case ATTACK: EnemyAttacked++;
        break;
    case DEFEND: EnemyDefended++;
        break;
    case GRAPPLE: EnemyGrappled++;
        break;
    case PARRY: EnemyParried++;
        break;
    }
}
void Character::SetOpponent(Character* aOpponent)
{
    // Storing the memory adress of the character's opponent
    OpponentID = aOpponent;
}
void Character::Attack()
{
    ActionName = "attack";
    // Looks at how well the action is carried out
    switch (Match(*OpponentID))
    {
        // Carries out the action
    case NORMAL:
        ActionName = "Attack";
        OpponentID->Hp -= Damage;
        std::cout << Name << " readies their attack and gets a good strike " << std::endl;
        break;
    case WEAK:
        ActionName = "Weak Attack";
        OpponentID->Hp -= Damage / 2;
        std::cout << Name << " readies their attack and strike " << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " readies their attack, but can't hit " << OpponentID->Name << std::endl;
        break;
    case COUNTERED:
        std::cout << Name << " readies their " << ActionName << ", but gets countered, letting " << OpponentID->Name << " stun them " << std::endl;
        ActionName = "Countered";
        isStunned = true;
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Defend()
{
    switch (Match(*OpponentID))
    {
    case NORMAL:
        ActionName = "Defend";
        OpponentID->isProne = true;
        std::cout << Name << " prepares against a grapple, and knocks " << OpponentID->Name << " prone " << std::endl;
        break;
    case WEAK:
        ActionName = "Weak Defend";
        std::cout << Name << " weakly prepares against a grapple, and manages to hold " << OpponentID->Name << " back" << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " prepares against a grapple, but can't do anything " << std::endl;
        break;
    case COUNTERED:
        ActionName = "Countered";
        std::cout << Name << " prepares against a grapple, but gets punched by " << OpponentID->Name << " instead " << std::endl;
        isStunned = true;
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Grapple()
{
    ActionName = "grapple";
    switch (Match(*OpponentID))
    {
    case NORMAL:
        ActionName = "Grapple";
        OpponentID->Hp -= OpponentID->Damage/2;
        OpponentID->isProne = true;
        std::cout << Name << " grabs " << OpponentID->Name << "'s legs, and tackles them to the ground " << std::endl;
        break;
    case WEAK:
        ActionName = "Weak Grapple";
        OpponentID->isProne = true;
        std::cout << Name << " grabs " << OpponentID->Name << "'s arm and leg, and flips them on their back " << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " tries to flip " << OpponentID->Name << " on their back, but can't " << std::endl;
        break;
    case COUNTERED:
        std::cout << Name << " readies their " << ActionName << ", but gets countered, letting " << OpponentID->Name << " stun them " << std::endl;
        ActionName = "Countered";
        isStunned = true;
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Parry()
{
    ActionName = "parry";
    switch (Match(*OpponentID))
    {
    case NORMAL:
        ActionName = "Parry";
        OpponentID->isProne = true;
        std::cout << Name << " prepares against an attack, and knocks " << OpponentID->Name << " prone, stunning them for a moment " << std::endl;
        break;
    case WEAK:
        ActionName = "Weak Parry";
        OpponentID->isProne = true;
        std::cout << Name << " weakly prepares against an attack, and knocks " << OpponentID->Name << " prone " << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " prepares against an attack, but can't do anything " << std::endl;
        break;
    case COUNTERED:
        std::cout << Name << " readies their " << ActionName << ", but gets countered, letting " << OpponentID->Name << " stun them " << std::endl;
        ActionName = "Countered";
        isStunned = true;
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}