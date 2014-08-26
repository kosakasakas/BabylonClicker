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
#include "BattleController.h"

BossFactory::BossFactory()
{
}

BossFactory::~BossFactory()
{
}

GameObject* BossFactory::createObject(int objectID) {
    return create(objectID, 0);
}

GameObject* BossFactory::create(int objectID, int level) {
    BossDataFactory* bdFactory = new BossDataFactory("bossData.plist");
    BossData* bData = (BossData*)bdFactory->create(objectID);
    CC_SAFE_RELEASE(bdFactory);
    Boss* boss = new Boss(bData, level);
    return boss;
}