//
//  Unit.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Unit.h"
#include "BattleController.h"
#include "UnitNode.h"

Unit::Unit(UnitData* data)
: GameObject(data)
{
    unitNode = new UnitNode(this);
}

Unit::~Unit()
{
    unitNode->release();
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

void Unit::onAction() {
    CCLOG("Unit onAction called");
    attack();
}

bool Unit::isHoldingNode() {
    return (unitNode != NULL) ? true : false;
}

void Unit::dump() {
    ((UnitData*)objectData)->dump();
    CCLOG("isHoldingNode: %d", isHoldingNode());
}