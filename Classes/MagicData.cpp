//
//  MagicData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "MagicData.h"

MagicData::MagicData(Dictionary* data)
: ObjectData(data)
{
}

MagicData::~MagicData()
{
}

const char* MagicData::getObjectType() {
    return "magic";
}