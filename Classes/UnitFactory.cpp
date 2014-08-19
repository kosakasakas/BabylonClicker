//
//  UnitFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "UnitFactory.h"
#include "Unit.h"
#include "cocos2d.h"
#include "UnitDataFactory.h"
#include "BattleController.h"

USING_NS_CC;

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

GameObject* UnitFactory::createObject(int objectID) {
    UnitData* uData;
    if(BattleController::getInstance()->isHavingSharedUnitData(objectID)) {
        uData = BattleController::getInstance()->getSharedUnitData(objectID);
        uData->retain();
    } else {
        UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
        uData = (UnitData*)udFactory->create(objectID);
        BattleController* bc = BattleController::getInstance();
        bc->setSharedUnitData(uData);
        Field* field = bc->getField();
        uData->dump();
        field->registUnitFamiryFieldObserver(uData);
        field->registUnitMagicFieldObserver(uData);
    }
    Unit* unit = new Unit(uData);
    return unit;
}