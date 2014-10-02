//
//  ItemData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "ItemData.h"

ItemData::ItemData(Dictionary* data)
: ObjectData(data)
{
}

ItemData::~ItemData()
{
}

const char* ItemData::getObjectType() const{
    return "item";
}