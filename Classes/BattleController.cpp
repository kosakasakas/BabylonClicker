//
//  BattleController.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BattleController.h"
#include "BossFactory.h"
#include "GameController.h"
#include "UnitField.h"

USING_NS_CC;

BattleController* BattleController::_singleton = NULL;

BattleController::BattleController()
{
    BossFactory* bFactory = new BossFactory();
    targetBoss = (Boss*)bFactory->create(0); // todo set index from field object.
    activeUnitCage = new UnitCage(GameController::getInstance()->getConfig()->getMaxUnitNum());
    field = new Field();
}

BattleController::~BattleController()
{
    field->release();
    targetBoss->release();
    activeUnitCage->release();
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
    BossFactory* bFactory = new BossFactory();
    targetBoss = (Boss*)bFactory->create(1); // todo set index from field object.
    CCLOG("new boss is created..");
}


UnitData* BattleController::getSharedUnitData(int objectID) const {
    UnitField* uf = dynamic_cast<UnitField*>(field->getUnitField()->getObjectAtIndex(objectID));
    return uf->getSharedUnitData();
}

void BattleController::setSharedUnitData(UnitData* unitData) {
    UnitField* uf = dynamic_cast<UnitField*>(field->getUnitField()->getObjectAtIndex(unitData->getObjectID()));
    uf->setSharedUnitData(unitData);
}

bool BattleController::isHavingSharedUnitData(int objectID) const {
    UnitField* uf = dynamic_cast<UnitField*>(field->getUnitField()->getObjectAtIndex(objectID));
    return (uf->isHoldingSharedUnitData()) ? true : false;
}