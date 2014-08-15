
//
//  BossData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "BossData.h"

const char* BossData::HP_KEY = "hp";

BossData::BossData(Dictionary* data)
:UnitData(data)
{
}

BossData::~BossData()
{
}

float BossData::getHP() {
    return getFloatValue(HP_KEY);
}

void BossData::dump() {
    UnitData::dump();
    CCLOG("hp: %f", getHP());
}