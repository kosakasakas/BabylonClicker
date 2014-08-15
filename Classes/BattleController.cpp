//
//  BattleController.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "BattleController.h"
#include "BossFactory.h"

USING_NS_CC;

BattleController* BattleController::_singleton = NULL;

BattleController::BattleController()
{
    BossFactory* bFactory = new BossFactory();
    targetBoss = (Boss*)bFactory->create(0); // todo set index from field object.
}

BattleController::~BattleController()
{
}

BattleController* BattleController::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new BattleController();
    }
    return _singleton;
}