//
//  UnitCage.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "UnitCage.h"
#include "UnitNode.h"
#include "BattleController.h"
#include "UnitField.h"

UnitCage::UnitCage(int unitNum)
: maxUnitNum(unitNum)
{
    unitArray = Array::createWithCapacity(unitNum);
    unitArray->retain();
}

UnitCage::~UnitCage()
{
    unitArray->release();
}

void UnitCage::addUnit(Unit *unit) {
    if (canAddUnit()) {
        unitArray->addObject(unit);
        UnitData* ud = (UnitData*)unit->getObjectData();
        ud->incrementUnitNum();
        Array* unitRef = BattleController::getInstance()->getField()->getUnitRefArray(unit->getObjectData()->getObjectID());
        unitRef->addObject(unit);
    } else {
        CCLOG("active unit num is already over..");
    }
}

void UnitCage::removeUnit(Unit* unit) {
    unitArray->removeObject(unit);
    const char* name = unit->getObjectData()->getName();
    UnitData* ud = (UnitData*)unit->getObjectData();
    ud->reduceUnitNum(1);
    Array* unitRef = BattleController::getInstance()->getField()->getUnitRefArray(unit->getObjectData()->getObjectID());
    unitRef->removeObject(unit);
    unit->release();
    CCLOG("remove unit: %s", name);
}

bool UnitCage::canAddUnit() const{
    return (unitArray->count() < maxUnitNum) ? true : false;
}

void UnitCage::attackAll() {
    Object *it;
    CCARRAY_FOREACH(unitArray, it)
    {
        Unit* unit = dynamic_cast<Unit*>(it);
        unit->attack();
    }
}

void UnitCage::dump() const{
    CCLOG("======UnitCage Class======");
    CCLOG("maxUnitNum: %d", maxUnitNum);
    CCLOG("holdUnitNum: %d", unitArray->count());
    CCLOG("unitArray RetainCount: %d", unitArray->retainCount());
    Object *it;
    CCARRAY_FOREACH(unitArray, it)
    {
        Unit* unit = dynamic_cast<Unit*>(it);
        unit->dump();
    }
    CCLOG("UnitCage dump end..");
}