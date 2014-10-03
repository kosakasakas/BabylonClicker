//
//  BattleController.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BattleController.h"
#include "RandomBossFactory.h"
#include "UnitField.h"

USING_NS_CC;

BattleController* BattleController::_singleton = NULL;

BattleController::BattleController()
: mainScene(NULL)
{
    config = new GameConfig();
    BossFactory* bFactory = new BossFactory();
    targetBoss = (Boss*)bFactory->create(0);
    activeUnitCage = new UnitCage(config->getMaxUnitNum());
    field = new Field();
    critical = new CriticalSubjectNode();
    critical->schedule(schedule_selector(CriticalSubjectNode::onUpdateCriticalLot), config->getCriticalInterval());
    CC_SAFE_RELEASE(bFactory);
}

BattleController::~BattleController()
{
    field->release();
    targetBoss->release();
    activeUnitCage->release();
    critical->unscheduleAllSelectors();
    critical->release();
    config->release();
    mainScene->release();
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
    if(mainScene) targetBoss->summon(mainScene->getBattleViewNode());
    mainScene->updateBattleVeiw();
    CCLOG("new boss is created..");
    targetBoss->dump();
    CC_SAFE_RELEASE(rbFactory);
}
