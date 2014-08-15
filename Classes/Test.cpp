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
#include "Unit.h"
#include "User.h"
#include "Magic.h"
#include "cocos2d.h"
#include "UnitDataFactory.h"
#include "UnitData.h"

USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}

void Test::run() {
    
    CCLOG("******Settings******");
    
    /*
    CCLOG("******UnitDataFactory class******");
    UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
    udFactory->dump();
    UnitData* uData = (UnitData*)udFactory->create(0);
    uData->dump();
    uData->setCost(100);
    uData->setLevel(50);
    uData->dump();
     */
    
    CCLOG("******User class******");
    User* user = (User*)GameController::getInstance()->getUser();
    user->setSoul(100);
    user->dump();
    
    CCLOG("******Unit class******");
    UnitFactory* ufact = new UnitFactory();
    Unit* unit = (Unit*)ufact->create(0);
    unit->dump();
    unit = (Unit*)ufact->create(3);
    unit->dump();
    unit = (Unit*)ufact->create(5);
    unit->dump();
    
    Boss* boss = BattleController::getInstance()->getTargetBoss();
    boss->dump();
    
    CCLOG("******Item class******");
    ItemFactory* ifact = new ItemFactory();
    Item* item = (Item*)ifact->create(0);
    item->dump();
    
    CCLOG("******Magic class******");
    MagicFactory* mfact = new MagicFactory();
    Magic* magic = (Magic*)mfact->create(0);
    magic->dump();
    
    CCLOG("******BattleController class******");
    
    CCLOG("******Field class******");
    GameController::getInstance()->getField()->dump();
    GameController::getInstance()->getField()->setMaxActiveUnitNum(100);
    GameController::getInstance()->getField()->setMaxInctiveUnitNum(10);
    GameController::getInstance()->getField()->setMarikaOffset(3.f);
    GameController::getInstance()->getField()->setHanaarukiOffset(2.f);
    GameController::getInstance()->getField()->setBabylonOffset(4.f);
    GameController::getInstance()->getField()->dump();
}