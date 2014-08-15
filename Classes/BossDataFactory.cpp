//
//  BossDataFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "BossDataFactory.h"
#include "BossData.h"

BossDataFactory::BossDataFactory(const char* filePath)
: UnitDataFactory(filePath)
{
}

BossDataFactory::~BossDataFactory()
{
}

ObjectData* BossDataFactory::createObjectData(int index){
    BossData* bdata = new BossData(getPropertyValueAtIndex(index));
    return bdata;
}