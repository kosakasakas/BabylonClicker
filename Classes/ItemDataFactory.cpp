//
//  ItemDataFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "ItemDataFactory.h"
#include "ItemData.h"

ItemDataFactory::ItemDataFactory(const char* filePath)
: ObjectDataFactory(filePath)
{
}

ItemDataFactory::~ItemDataFactory()
{
}

ObjectData* ItemDataFactory::createObjectData(int index) {
    ItemData* idata = new ItemData(getPropertyValueAtIndex(index));
    return idata;
}