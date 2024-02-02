#include "matcher.h"

int Match(Character aPerson)
{
    // Gets the result of the matchup
    int result = Index(aPerson.Action, (*(aPerson.OpponentID)).Action);
    // Weakens the action if prone
    if ((*(aPerson.OpponentID)).isProne == true && result < 2)
    {
        return result + 1;
    }
    else
    {
        return result;
    }
}

int Index(int TargetAction, int ActingAction)
{
    // Compares every matchup and returns how well the Acting character's actions went,
    // for example Parry -> Attack and the Acting character is attacking
    switch (ActingAction) 
    {
        case ATTACK: // It would go there
            switch (TargetAction) {
            case ATTACK: return WEAK;
            case DEFEND: return NORMAL;
            case GRAPPLE: return WEAK;
            case PARRY: return COUNTERED; // And then there, the result is that he gets countered
            default: return NORMAL;
            }
        case DEFEND:
            switch (TargetAction) {
            case ATTACK: return COUNTERED;
            case DEFEND: return NOTHING;
            case GRAPPLE: return NORMAL;
            case PARRY: return NOTHING;
            default: return NOTHING;
            }
        case GRAPPLE:
            switch (TargetAction) {
            case ATTACK: return NORMAL;
            case DEFEND: return COUNTERED;
            case GRAPPLE: return WEAK;
            case PARRY: return NORMAL;
            default: return NORMAL;
            }
        case PARRY:
            switch (TargetAction) {
            case ATTACK: return NORMAL;
            case DEFEND: return NOTHING;
            case GRAPPLE: return COUNTERED;
            case PARRY: return NOTHING;
            default: return NOTHING;
            }
        case STRUGGLE:
            switch (TargetAction) {
            case ATTACK: return NORMAL;
            case DEFEND: return NORMAL;
            case GRAPPLE: return COUNTERED;
            case PARRY: return NORMAL;
            default: return NORMAL;
            }
        case REINFORCE:
            switch (TargetAction) {
            case ATTACK: return NORMAL;
            case DEFEND: return COUNTERED;
            case GRAPPLE: return NORMAL;
            case PARRY: return NORMAL;
            default: return NORMAL;
            }
        default:
            return COUNTERED;
    }
}