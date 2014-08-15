//
//  MagicDataFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "MagicDataFactory.h"
#include "MagicData.h"

MagicDataFactory::MagicDataFactory(const char* filePath)
: ObjectDataFactory(filePath)
{
}

MagicDataFactory::~MagicDataFactory()
{
}

ObjectData* MagicDataFactory::createObjectData(int index){
    MagicData* mdata = new MagicData(getPropertyValueAtIndex(index));
    return mdata;
}