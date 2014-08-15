//
//  BossFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BossFactory.h"
#include "Boss.h"
#include "BossData.h"
#include "BossDataFactory.h"

BossFactory::BossFactory()
{
}

BossFactory::~BossFactory()
{
}

GameObject* BossFactory::createObject(int objectID) {
    BossDataFactory* bdFactory = new BossDataFactory("BossData.plist");
    BossData* bData = (BossData*)bdFactory->create(objectID);
    Boss* boss = new Boss(bData);
    return boss;
}