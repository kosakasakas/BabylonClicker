//
//  UnitCage.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "UnitCage.h"
#include "UnitNode.h"

UnitCage::UnitCage(int unitNum)
: maxUnitNum(unitNum)
{
    unitArray = Array::create();
}

UnitCage::~UnitCage()
{
    unitArray->release();
}

void UnitCage::addUnit(Unit *unit) {
    if (canAddUnit()) {
        unitArray->addObject(unit);
        //scheduleOnce(schedule_selector(unit->onAction, 1.0));
    } else {
        CCLOG("active unit num is already over..");
    }
}

bool UnitCage::canAddUnit() {
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

void UnitCage::dump() {
    CCLOG("======UnitCage Class======");
    CCLOG("maxUnitNum: %d", maxUnitNum);
    CCLOG("holdUnitNum: %d", unitArray->count());
    Object *it;
    CCARRAY_FOREACH(unitArray, it)
    {
        Unit* unit = dynamic_cast<Unit*>(it);
        unit->dump();
    }
    CCLOG("UnitCage dump end..");
}