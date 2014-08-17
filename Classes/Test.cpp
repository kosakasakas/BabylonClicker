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
#include "GameConfig.h"

USING_NS_CC;

Test::Test()
{
}

Test::~Test()
{
}

void Test::run() {
    
    CCLOG("******Settings******");
    
    CCLOG("******UnitDataFactory class******");
    GameConfig* config = GameController::getInstance()->getConfig();
    config->dump();
    
    CCLOG("******User class******");
    User* user = (User*)GameController::getInstance()->getUser();
    user->setSoul(100);
    user->dump();
    
    CCLOG("******Unit class******");
    UnitCage* cage = BattleController::getInstance()->getActiveUnitCage();
    UnitFactory* ufact = new UnitFactory();
    Unit* unit1 = (Unit*)ufact->create(0);
    Unit* unit2 = (Unit*)ufact->create(3);
    Unit* unit3 = (Unit*)ufact->create(5);
    Unit* unit4 = (Unit*)ufact->create(2);
    cage->addUnit(unit1);
    cage->addUnit(unit2);
    cage->addUnit(unit3);
    cage->addUnit(unit4);
    cage->dump();
    
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
    GameController::getInstance()->getField()->setMarikaOffset(3.f);
    GameController::getInstance()->getField()->setHanaarukiOffset(2.f);
    GameController::getInstance()->getField()->setBabylonOffset(4.f);
    GameController::getInstance()->getField()->dump();
}