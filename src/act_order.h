#ifndef ACTORDER_H
#define ACTORDER_H
#include "character.h"
class ActOrder
{
    static void Action(Character* Actor);
public:
    static void Act(Character* Actor1, Character* Actor2,  Character* Actor3);
};
#endif