//
//  UnitData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "UnitData.h"
#include "BattleController.h"

const char* UnitData::ATTACK_KEY = "attack";
const char* UnitData::INTERVAL_KEY = "interval";
const char* UnitData::MAGIC_KEY = "magic";
const char* UnitData::FAMILY_KEY = "family";
const char* UnitData::ATTACK_GROWTH_KEY = "attackGrouth";

UnitData::UnitData(Dictionary* data)
: ObjectData(data)
, unitNum(0)
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
    updateAttack();
}

void UnitData::updateAttack() {
    attack = getDefaultAttack();
    addMagicOffsetToAttack();
    addFamilyOffsetToAttack();
}

void UnitData::addMagicOffsetToAttack() {
    int magicID = Field::getMagicFieldType(getMagic());
    FieldObject* fo = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUnitMagicField()->getObjectAtIndex(magicID));
    int level = fo->getLevel();
    float aGrouth = getFloatValue(ATTACK_GROWTH_KEY);
    for(int i = 0; i < level; i++) {
        attack *= aGrouth;
    }
}

void UnitData::addFamilyOffsetToAttack() {
    int familyID = Field::getFamilyFieldType(getFamily());
    FieldObject* fo = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUnitMagicField()->getObjectAtIndex(familyID));
    int level = fo->getLevel();
    float aGrouth = getFloatValue(ATTACK_GROWTH_KEY);
    for(int i = 0; i < level; i++) {
        attack *= aGrouth;
    }
}

void UnitData::incrementUnitNum() {
    ++unitNum;
}

void UnitData::reduceUnitNum(int num) {
    unitNum -= num;
}

void UnitData::dump() const{
    ObjectData::dump();
    CCLOG("attack: %f", getAttack());
    CCLOG("interval: %f", getInterval());
    CCLOG("family: %s", getFamily());
    CCLOG("magic: %s", getMagic());
}