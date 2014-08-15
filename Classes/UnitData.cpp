//
//  UnitData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "UnitData.h"

const char* UnitData::ATTACK_KEY = "attack";

UnitData::UnitData(Dictionary* data)
: ObjectData(data)
{
}

UnitData::~UnitData()
{
}

float UnitData::getAttack() {
    return getFloatValue(ATTACK_KEY);
}

void UnitData::dump() {
    ObjectData::dump();
    CCLOG("attack: %f", getAttack());
}