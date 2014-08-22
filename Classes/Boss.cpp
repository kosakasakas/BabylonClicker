//
//  Boss.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Boss.h"
#include "BattleController.h"
#include "BossDataDisplay.h"

Boss::Boss(BossData* data, int level)
: Unit(data)
{
    BossDataDisplay* bdDisplay = new BossDataDisplay();
    data->registerObserver(bdDisplay);
    ((BossData*)objectData)->setLevel(level);
}

Boss::~Boss()
{
}

void Boss::damage(float val) {
    BossData* bData = (BossData*)objectData;
    (bData)->reduceHP(val);
    
    if (bData->getHP() <= 0) {
        onDestroyed();
    }
}

void Boss::onDestroyed() {
    CCLOG("Boss is destroyed..");
    BattleController* bc = BattleController::getInstance();
    int currentLevel = objectData->getLevel();
    bc->getField()->setBossLevel(objectData->getObjectID(), ++currentLevel);
    bc->onTargetBossDestroyed();
}