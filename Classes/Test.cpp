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
#include "GameData.h"

USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}

void Test::run() {
    
    CCLOG("******Settings******");
    
    
    CCLOG("******GmaeData Class******");
    GameData* uData = new GameData("unitData.plist");
    uData->dump();
    uData->dumpPropertyValueAtIndex(0);
    uData->dumpPropertyValueAtIndex(5);
    uData->dumpPropertyValueAtIndex(10);
    
    CCLOG("******User class******");
    User* user = (User*)GameController::getInstance()->getUser();
    user->setSoul(100);
    user->dump();
    
    CCLOG("******Unit class******");
    UnitFactory* ufact = new UnitFactory();
    Unit* unit = (Unit*)ufact->create();
    unit->dump();
    
    CCLOG("******Item class******");
    ItemFactory* ifact = new ItemFactory();
    Item* item = (Item*)ifact->create();
    item->dump();
    
    CCLOG("******Magic class******");
    MagicFactory* mfact = new MagicFactory();
    Magic* magic = (Magic*)mfact->create();
    magic->dump();
    
    CCLOG("******BattleController class******");
    CCLOG("who are you?: %s",BattleController::getInstance()->getTargetBoss()->say());
    
    CCLOG("******Field class******");
    GameController::getInstance()->getField()->dump();
    GameController::getInstance()->getField()->setMaxActiveUnitNum(100);
    GameController::getInstance()->getField()->setMaxInctiveUnitNum(10);
    GameController::getInstance()->getField()->setMarikaOffset(3.f);
    GameController::getInstance()->getField()->setHanaarukiOffset(2.f);
    GameController::getInstance()->getField()->setBabylonOffset(4.f);
    GameController::getInstance()->getField()->dump();
}