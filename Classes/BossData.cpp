
//
//  BossData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "BossData.h"

const char* BossData::HP_KEY = "hp";
const char* BossData::HP_GROWTH_KEY = "hpGrowth";
const char* BossData::LOT_WEIGHT_KEY = "lotWeight";

BossData::BossData(Dictionary* data)
:UnitData(data)
{
    updateHP();
}

BossData::~BossData()
{
}

void BossData::updateHP() {
    hp = getDefaultHP();
    float growth = getHpGrowth();
    for(int i = 0; i < level; i++) {
        hp *= growth;
    }
}

float BossData::getDefaultHP() const{
    return getFloatValue(HP_KEY);
}

float BossData::getHpGrowth() const{
    return getFloatValue(HP_GROWTH_KEY);
}

float BossData::getLotWeight() const {
    return getFloatValue(LOT_WEIGHT_KEY);
}

void BossData::reduceHP(float damage) {
    hp -= damage;
    notifyObservers();
}

void BossData::update() {
    ObjectData::update();
    updateHP();
}

void BossData::dump() const{
    UnitData::dump();
    CCLOG("hp: %f", hp);
}

const char* BossData::getObjectType() {
    return "boss";
}