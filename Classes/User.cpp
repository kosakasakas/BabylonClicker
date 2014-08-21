//
//  User.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "User.h"

User::User()
: soul(10000.f)
{
}

User::~User()
{
}

void User::dump() const{
    CCLOG("======User Class======");
    CCLOG("soul : %f", soul);
}

void User::addSoul(float val) {
    soul += val;
}

void User::reduceSoul(float val) {
    if (soul >= val) {
        soul -= val;
    } else {
        CCLOG("can not reduce soul any more!");
    }
}