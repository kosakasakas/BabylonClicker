//
//  Test.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Test.h"
#include "GameController.h"
#include "ItemFactory.h"
#include "MagicFactory.h"
#include "UnitFactory.h"
#include "BossFactory.h"
#include "Item.h"
#include "BattleController.h"

Test::Test()
{
}

Test::~Test()
{
}

void Test::run() {
    CCLOG("======say:%s======",GameController::getInstance()->getUnitFactory()->create()->say());
    CCLOG("======say:%s======",GameController::getInstance()->getItemFactory()->create()->say());
    CCLOG("======say:%s======",GameController::getInstance()->getMagicFactory()->create()->say());
    CCLOG("======say:%s======",GameController::getInstance()->getBossFactory()->create()->say());
    
    CCLOG("======BattleController class======");
    CCLOG("who are you?: %s",BattleController::getInstance()->getTargetBoss()->say());
}