//
//  BossFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BossFactory.h"
#include "Boss.h"

BossFactory::BossFactory()
{
}

BossFactory::~BossFactory()
{
}

GameObject* BossFactory::createObject(int objectID) {
    Boss* boss = new Boss();
    return boss;
}