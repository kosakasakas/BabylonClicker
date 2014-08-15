//
//  GameController.cpp
//  UnicornEngine
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#include "GameController.h"

USING_NS_CC;

GameController* GameController::_singleton = NULL;

GameController::GameController()
{
    unitFactory = new UnitFactory();
    itemFactory = new ItemFactory();
    magicFactory = new MagicFactory();
    bossFactory = new BossFactory();
    field = new Field();
    user = new User();
}

GameController::~GameController()
{
    unitFactory->release();
    itemFactory->release();
    magicFactory->release();
    bossFactory->release();
    delete field;
    delete user;
}

GameController* GameController::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new GameController();
    }
    return _singleton;
}
