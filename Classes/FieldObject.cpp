//
//  FieldObject.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/18.
//
//

#include "FieldObject.h"

FieldObject::FieldObject()
: level(0)
{
}

FieldObject::~FieldObject()
{
}

void FieldObject::dump() const {
    CCLOG("FieldObject Class");
    CCLOG("level: %d", level);
}

void FieldObject::incrementLevel() {
    ++level;
}