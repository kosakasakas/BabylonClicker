//
//  BossDataDisplay.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "BossDataDisplay.h"
#include "BossData.h"

BossDataDisplay::BossDataDisplay()
{
}

BossDataDisplay::~BossDataDisplay()
{
}

void BossDataDisplay::update(const ObjectData* data) {
    draw(data);
}

void BossDataDisplay::draw(const ObjectData* data) {
    BossData* bData = (BossData*)data;
    CCLOG("Boss name: %s", bData->getName());
    CCLOG("Boss hp: %f", bData->getHP());
}