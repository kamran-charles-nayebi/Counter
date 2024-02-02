#ifndef ACTORDER_H
#define ACTORDER_H
#include "character.h"
class ActOrder
{
private:
    void Action(Character* Actor);
public:
    void Act(Character* Actor1, Character* Actor2);
};
#endif