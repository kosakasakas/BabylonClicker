//
//  GameController.cpp
//  UnicornEngine
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#include "GameController.h"
#include "cocos2d.h"

USING_NS_CC;

GameController* GameController::_singleton = NULL;

GameController::GameController()
{
    unitFactory = new UnitFactory();
    itemFactory = new ItemFactory();
    magicFactory = new MagicFactory();
}

GameController::~GameController()
{
    unitFactory->release();
    itemFactory->release();
    magicFactory->release();
}

GameController* GameController::getInstance()
{
    if( NULL == _singleton )
    {
        _singleton = new GameController();
    }
    return _singleton;
}
