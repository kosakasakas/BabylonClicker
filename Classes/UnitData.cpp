//
//  UnitData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "UnitData.h"

const char* UnitData::ATTACK_KEY = "attack";
const char* UnitData::INTERVAL_KEY = "interval";
const char* UnitData::MAGIC_KEY = "magic";
const char* UnitData::FAMILY_KEY = "family";
const char* UnitData::ATTACK_GROUTH_KEY = "attackGrouth";

UnitData::UnitData(Dictionary* data)
: ObjectData(data)
{
    attack = getDefaultAttack();
}

UnitData::~UnitData()
{
}

float UnitData::getDefaultAttack() const{
    return getFloatValue(ATTACK_KEY);
}

float UnitData::getInterval() const{
    return getFloatValue(INTERVAL_KEY);
}

const char* UnitData::getFamily() const {
    return getCharValue(FAMILY_KEY);
}

const char* UnitData::getMagic() const {
    return getCharValue(MAGIC_KEY);
}

void UnitData::updateStatus(const BaseObject* bo) {
    const FieldObject* fo = dynamic_cast<const FieldObject*>(bo);
    updateAttack(fo);
}

void UnitData::updateAttack(const FieldObject* fo) {
    int level = fo->getLevel();
    float defAttack = getDefaultAttack();
    float aGrouth = getFloatValue(ATTACK_GROUTH_KEY);
    for(int i = 0; i < level; i++) {
        defAttack *= aGrouth;
    }
    attack = defAttack;
}

void UnitData::dump() const{
    ObjectData::dump();
    CCLOG("attack: %f", getAttack());
    CCLOG("interval: %f", getInterval());
    CCLOG("family: %s", getFamily());
    CCLOG("magic: %s", getMagic());
}