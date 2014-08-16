//
//  GameConfig.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "GameConfig.h"
#include "ObjectDataFactory.h"

GameConfig::GameConfig()
{
    ObjectDataFactory* odFactory = new ObjectDataFactory("config.plist");
    data = odFactory->create(0);
}

GameConfig::~GameConfig()
{
    data->release();
}

int GameConfig::getAttackInterval() {
    return data->getIntValue("interval");
}

int GameConfig::getMaxUnitNum() {
    return data->getIntValue("maxUnitNum");
}

const char* GameConfig::getNendSpotID() {
    return data->getCharValue("nendSpotID");
}

const char* GameConfig::getNendApiKey() {
    return data->getCharValue("nendApiKey");
}

void GameConfig::dump() {
    CCLOG("======GameConfig Class======");
    CCLOG("interval: %d", getAttackInterval());
    CCLOG("maxUnitNum: %d", getMaxUnitNum());
    CCLOG("nendSpotID: %s", getNendSpotID());
    CCLOG("nendApiKey: %s", getNendApiKey());
}