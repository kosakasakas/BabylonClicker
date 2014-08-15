//
//  UnitCage.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "UnitCage.h"

UnitCage::UnitCage(int unitNum)
: maxUnitNum(unitNum)
{
    unitcage = Array::create();
}

UnitCage::~UnitCage()
{
    unitcage->release();
}

void UnitCage::addUnit(Unit *unit) {
    if (canAddUnit()) {
        unitcage->addObject(unit);
    } else {
        CCLOG("active unit num is already over..");
    }
}

bool UnitCage::canAddUnit() {
    return (unitcage->count() < maxUnitNum) ? true : false;
}

void UnitCage::attackAll() {
    Object *it;
    CCARRAY_FOREACH(unitcage, it)
    {
        Unit* unit = dynamic_cast<Unit*>(it);
        unit->attack();
    }
}

void UnitCage::dump() {
    CCLOG("======UnitCage Class======");
    CCLOG("maxUnitNum: %d", maxUnitNum);
    CCLOG("holdUnitNum: %d", unitcage->count());
    Object *it;
    CCARRAY_FOREACH(unitcage, it)
    {
        Unit* unit = dynamic_cast<Unit*>(it);
        unit->dump();
    }
    CCLOG("UnitCage dump end..");
}