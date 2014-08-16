//
//  Unit.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Unit.h"
#include "BattleController.h"

Unit::Unit(UnitData* data)
: GameObject(data)
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

void Unit::attack() {
    UnitData* uData = (UnitData*)objectData;
    CCLOG("Attacker name: %s", uData->getName());
    CCLOG("Attacker power: %f", uData->getAttack());
    float attack = uData->getAttack();
    BattleController::getInstance()->getTargetBoss()->damage(attack);
}