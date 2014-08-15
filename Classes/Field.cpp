//
//  Field.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Field.h"

Field::Field()
: maxActiveUnitNum(50)
, maxInactiveUnitNum(50)
, babylonOffset(1.0f)
, marikaOffset(1.0f)
, hanaarukiOffset(1.0f)
{
}

Field::~Field()
{
}

void Field::dump() {
    CCLOG("======Field Class======");
    CCLOG("maxActiveUnitNum: %d", maxActiveUnitNum);
    CCLOG("maxInactiveUnitNum: %d", maxInactiveUnitNum);
    CCLOG("babylonOffset: %f", babylonOffset);
    CCLOG("marikaOffset: %f", marikaOffset);
    CCLOG("hanaarukiOffset: %f", hanaarukiOffset);
}