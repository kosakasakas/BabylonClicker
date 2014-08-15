//
//  Boss.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Boss.h"
#include "BattleController.h"

Boss::Boss(BossData* data)
: Unit(data)
{
}

Boss::~Boss()
{
}

const char* Boss::say() {
    return "Im boss. haha!";
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
    BattleController::getInstance()->onTargetBossDestroyed();
}