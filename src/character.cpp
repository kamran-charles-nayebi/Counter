#include "character.h"
#include "matcher.h"

Character::Character()
    :Name("Default"), isPlayer(false), Action(0), isProne(false), Hp(200), Damage(40), isStunned(false), Cooldown(0),
    ActionName("Idle"), Limit(4), PlayerAttacked(0), PlayerDefended(0), PlayerGrappled(0), PlayerParried(0)
{}
void Character::Setup()
{
    // Resetting the action limit
        Limit = 4;
    // Slowing stunned characters
    if(Cooldown > 1)
    {
        Cooldown--;
    }
    else if (Cooldown == 1)
    {
        Speed *= 2;
        Cooldown--;
    }
    // Making it so stunned characters don't take their turn
    if (isStunned)
    {
        isStunned = false;
        ActionName = "Stunned";
        Action = 0;
        Speed /= 2;
        Cooldown = 2;
    }
}
void Character::Input()
{
    if(isPlayer)
    {
        // Taking in the player's inputs and filtering out the incorrect ones
        while (!(std::cin >> Action) || Action > Limit)
        {
            std::cout << "Wrong input, please enter a correct action" << std::endl;
            std::cin.clear();
            std::cin.ignore(100, '\n');
        }
    } 
    else 
    // AI for enemy
    {
        Action = rand() % 4 + 1;
        // Will try to counter player if an action is used too much
        if (PlayerAttacked > 0)
        {
            if (PlayerAttacked >= 2)
            {
                Action = PARRY;
                PlayerAttacked--;        
            }
            PlayerAttacked -= 0.25f;
        }
        if (PlayerDefended > 0)
        {
            if (PlayerDefended >= 2)
            {
                Action = ATTACK;
                PlayerDefended--;
            }
            PlayerDefended -= 0.25f;
        }
        if (PlayerGrappled > 0)
        {
            if (PlayerGrappled >= 2)
            {
                Action = DEFEND;
                PlayerGrappled--;
            }
            PlayerGrappled -= 0.25f;
        }
        if (PlayerParried > 0)
        {
            if (PlayerParried >= 2)
            {
                Action = GRAPPLE;
                PlayerParried--;
            }
            PlayerParried -= 0.25f;
        }
        // Stores player's actions so it can counter them
        switch (OpponentID->Action)
        {
        case ATTACK: PlayerAttacked++;
            break;
        case DEFEND: PlayerDefended++;
            break;
        case GRAPPLE: PlayerGrappled++;
            break;
        case PARRY: PlayerParried++;
            break;
        }
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
    switch (Matcher::Match(OpponentID, this))
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
        ActionName = "Countered";
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Defend()
{
    switch (Matcher::Match(OpponentID, this))
    {
    case NORMAL:
        ActionName = "Defend";
        OpponentID->isProne = true;
        OpponentID->Status = "Prone";
        std::cout << Name << " prepares against a grapple, and knocks their opponent prone " << std::endl;
        if(OpponentID->isStunned)
        {
            OpponentID->Action = 0;
            OpponentID->ActionName = "Stunned";
        }
        break;
    case WEAK:
        ActionName = "Weak Defend";
        std::cout << Name << " weakly prepares against a grapple, and manages to hold their opponent back" << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " prepares against a grapple, but can't do anything " << std::endl;
        break;
    case COUNTERED:
        ActionName = "Countered";
        std::cout << Name << " prepares against a grapple, but gets punched instead " << std::endl;
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Grapple()
{
    ActionName = "grapple";
    switch (Matcher::Match(OpponentID, this))
    {
    case NORMAL:
        ActionName = "Grapple";
        OpponentID->Hp -= OpponentID->Damage/2;
        OpponentID->isProne = true;
        OpponentID->Status = "Prone";
        std::cout << Name << " grabs their opponent's legs, and tackles them to the ground " << std::endl;
        if(OpponentID->isStunned)
        {
            OpponentID->Action = 0;
            OpponentID->ActionName = "Stunned";
        }
        break;
    case WEAK:
        ActionName = "Weak Grapple";
        OpponentID->isProne = true;
        OpponentID->Status = "Prone";
        std::cout << Name << " grabs their opponent's arm and leg, and flips them on their back " << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " tries to flip their opponent on their back, but can't " << std::endl;
        break;
    case COUNTERED:
        ActionName = "Countered";
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::Parry()
{
    ActionName = "parry";
    switch (Matcher::Match(OpponentID, this))
    {
    case NORMAL:
        ActionName = "Parry";
        OpponentID->isProne = true;
        OpponentID->Status = "Prone";
        std::cout << Name << " prepares against an attack, and knocks their opponent prone, stunning them for a moment " << std::endl;
        if(OpponentID->isStunned)
        {
            OpponentID->Action = 0;
            OpponentID->ActionName = "Stunned";
        }
        break;
    case WEAK:
        ActionName = "Weak Parry";
        OpponentID->isProne = true;
        OpponentID->Status = "Prone";
        std::cout << Name << " weakly prepares against an attack, and knocks their opponent prone " << std::endl;
        break;
    case NOTHING:
        ActionName = "Nothing";
        std::cout << Name << " prepares against an attack, but can't do anything " << std::endl;
        break;
    case COUNTERED:
        ActionName = "Countered";
        break;
    default: std::cout << "ERROR" << std::endl;
        break;
    }
}
void Character::StandUp()
{
    ActionName = "Stand Up";
    std::cout << Name << " carefully stands up " << std::endl;
    isProne = false;
    Status = "Default";
}