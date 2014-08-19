//
//  UnitField.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/18.
//
//

#include "UnitField.h"

UnitField::UnitField()
: unitNum(0)
, sharedUnitData(NULL)
{
}

UnitField::~UnitField()
{
}

void UnitField::dump() const {
    FieldObject::dump();
    CCLOG("unitNum: %d", unitNum);
}

void UnitField::incrementUnitNum() {
    ++unitNum;
    notifyObservers();
}

void UnitField::decrementUnitNum() {
    --unitNum;
}

bool UnitField::isHoldingSharedUnitData() const {
    return (sharedUnitData != NULL) ? true : false;
}