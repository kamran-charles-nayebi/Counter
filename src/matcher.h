#ifndef MATCHER_H
#define MATCHER_H

#include "character.h"

class Matcher
{
    static int Index(const int TargetAction, const int ActingAction);
public:
    static int Match(const Character* aTarget, const Character* aActing);
};

#endif