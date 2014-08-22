//
//  RandomBossFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#include "RandomBossFactory.h"
#include "BossDataFactory.h"
#include "BattleController.h"

RandomBossFactory::RandomBossFactory()
{
    bossFactory = new BossFactory();
}

RandomBossFactory::~RandomBossFactory()
{
    bossFactory->release();
}

Boss* RandomBossFactory::create() {
    float lot = getRandomNum();
    Boss* boss;
    Field* fd = BattleController::getInstance()->getField();
    for(int i=0,n=fd->getBossNum(); i<n; ++i) {
        int bossLevel = fd->getBossLevel(i);
        boss = (Boss*)bossFactory->create(i, bossLevel);
        if (boss == NULL || lot <= 0) {
            return  NULL;
        }
        BossData* bd = (BossData*) boss->getObjectData();
        float lotWeight = bd->getLotWeight();
        if (lot < lotWeight) {
            return boss;
        }
        lot -= lotWeight;
    }
    return NULL;
}

float RandomBossFactory::getRandomNum() {
    int num = arc4random()%10000;
    return (float)num/100.f;
}