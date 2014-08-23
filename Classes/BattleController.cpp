//
//  BattleController.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BattleController.h"
#include "RandomBossFactory.h"
#include "GameController.h"
#include "UnitField.h"

USING_NS_CC;

BattleController* BattleController::_singleton = NULL;

BattleController::BattleController()
{
    BossFactory* bFactory = new BossFactory();
    targetBoss = (Boss*)bFactory->create(0); // todo load from saved data.
    activeUnitCage = new UnitCage(GameController::getInstance()->getConfig()->getMaxUnitNum());
    field = new Field();
    critical = new CriticalNode();
    critical->schedule(schedule_selector(CriticalNode::onScheduleUpdate), GameController::getInstance()->getConfig()->getCriticalInterval());
}

BattleController::~BattleController()
{
    field->release();
    targetBoss->release();
    activeUnitCage->release();
    critical->unscheduleAllSelectors();
    critical->release();
}

BattleController* BattleController::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new BattleController();
    }
    return _singleton;
}

void BattleController::onTargetBossDestroyed() {
    targetBoss->release();
    targetBoss = NULL;
    RandomBossFactory* rbFactory = new RandomBossFactory();
    targetBoss = (Boss*)rbFactory->create();
    CCLOG("new boss is created..");
    targetBoss->dump();
}