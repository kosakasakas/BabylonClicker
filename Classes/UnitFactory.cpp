//
//  UnitFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "UnitFactory.h"
#include "Unit.h"

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

GameObject* UnitFactory::createObject() {
    Unit* unit = new Unit();
    return unit;
}