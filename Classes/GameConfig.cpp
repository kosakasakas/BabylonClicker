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
    CC_SAFE_RELEASE(odFactory);
}

GameConfig::~GameConfig()
{
    data->release();
}

float GameConfig::getAttackInterval() const{
    return data->getFloatValue("interval");
}

int GameConfig::getMaxUnitNum() const{
    return data->getIntValue("maxUnitNum");
}

const char* GameConfig::getNendSpotID() const{
    return data->getCharValue("nendSpotID");
}

const char* GameConfig::getNendApiKey() const{
    return data->getCharValue("nendApiKey");
}

float GameConfig::getMagicOffsetRate() const {
    return data->getFloatValue("magicOffsetRate");
}

float GameConfig::getCriticalInterval() const {
    return data->getFloatValue("criticalInterval");
}

void GameConfig::dump() const{
    CCLOG("======GameConfig Class======");
    CCLOG("interval: %f", getAttackInterval());
    CCLOG("criticalInterval: %f", getCriticalInterval());
    CCLOG("maxUnitNum: %d", getMaxUnitNum());
    CCLOG("nendSpotID: %s", getNendSpotID());
    CCLOG("nendApiKey: %s", getNendApiKey());
}