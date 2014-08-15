//
//  UnitFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "UnitFactory.h"
#include "Unit.h"
#include "cocos2d.h"

USING_NS_CC;

UnitFactory::UnitFactory()
{
}

UnitFactory::~UnitFactory()
{
}

GameObject* UnitFactory::createObject(int ObjectID) {
    Unit* unit = new Unit();
    return unit;
    
    Dictionary *plistDic = Dictionary::createWithContentsOfFile("unitData.plist");
    String *name = (String*)((Array*)plistDic->objectForKey("name"))->objectAtIndex(ObjectID);
    String *cost = (String*)((Array*)plistDic->objectForKey("cost"))->objectAtIndex(ObjectID);
}