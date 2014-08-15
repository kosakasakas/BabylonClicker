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

USING_NS_CC;

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

GameObject* UnitFactory::createObject(int objectID) {
    UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
    UnitData* uData = (UnitData*)udFactory->create(objectID);
    Unit* unit = new Unit(uData);
    return unit;
}