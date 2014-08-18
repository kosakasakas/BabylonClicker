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
        int count = uData->retainCount();
        uData->retain();
    } else {
        UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
        uData = (UnitData*)udFactory->create(objectID);
        uData->retain();
        int count = uData->retainCount();
        BattleController::getInstance()->setSharedUnitData(uData);
    }
    Unit* unit = new Unit(uData);
    return unit;
}