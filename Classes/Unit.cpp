//
//  Unit.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Unit.h"

Unit::Unit()
{
}

Unit::~Unit()
{
}

const char* Unit::say(){
    return "Im Unit.";
}

void Unit::summon() {
    // 召喚された事を通知。ユニットカウントを上げる。
    CCLOG("Unit summon called");
}

bool Unit::canSummon() {
    return false;
}