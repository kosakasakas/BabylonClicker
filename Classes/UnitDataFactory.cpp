//
//  UnitDataFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "UnitDataFactory.h"
#include "UnitData.h"

UnitDataFactory::UnitDataFactory(const char* filePath)
: ObjectDataFactory(filePath)
{
}

UnitDataFactory::~UnitDataFactory()
{
}

ObjectData* UnitDataFactory::createObjectData(int index){
    UnitData* udata = new UnitData(getPropertyValueAtIndex(index));
    return udata;
}