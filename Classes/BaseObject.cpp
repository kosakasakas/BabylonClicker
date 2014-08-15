//
//  BaseObject.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BaseObject.h"
#include "cocos2d.h"

BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

void BaseObject::dump() {
    CCLOG("this object is not defined dump().");
}