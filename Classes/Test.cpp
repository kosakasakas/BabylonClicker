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

USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}

void Test::run() {
    
    CCLOG("******Settings******");
    Dictionary *plistDic = Dictionary::createWithContentsOfFile("unitData.plist");
    Array *nameArray = (Array*)plistDic->objectForKey("name");
    Array *costArray = (Array*)plistDic->objectForKey("cost");
    
    CCLOG("******User class******");
    User* user = (User*)GameController::getInstance()->getUser();
    user->setSoul(100);
    user->dump();
    
    CCLOG("******Unit class******");
    Unit* unit = (Unit*)GameController::getInstance()->getUnitFactory()->create();
    unit->dump();
    
    CCLOG("******Item class******");
    Item* item = (Item*)GameController::getInstance()->getItemFactory()->create();
    item->dump();
    
    CCLOG("******Magic class******");
    Magic* magic = (Magic*)GameController::getInstance()->getMagicFactory()->create();
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