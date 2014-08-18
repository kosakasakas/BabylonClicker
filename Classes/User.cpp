//
//  User.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "User.h"

User::User()
: soul(0)
{
}

User::~User()
{
}

void User::dump() const{
    CCLOG("======User Class======");
    CCLOG("soul : %d", soul);
}

void User::addSoul(int val) {
    soul += val;
}

void User::reduceSoul(int val) {
    if (soul >= val) {
        soul -= val;
    } else {
        CCLOG("can not reduce soul any more!");
    }
}