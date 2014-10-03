//
//  BossDataDisplay.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "BossDataDisplay.h"
#include "BossData.h"
#include "MainScene.h"
#include "BattleController.h"

BossDataDisplay::BossDataDisplay()
{
}

BossDataDisplay::~BossDataDisplay()
{
}

void BossDataDisplay::updateStatus(const BaseObject* data) {
    CCLOG("BossDataDisplay updated");
    
    MainScene* main = BattleController::getInstance()->getMainScene();
    if (main) {
        main->updateBattleVeiw();
    }
    draw(data);
}

void BossDataDisplay::draw(const BaseObject* data) {
    const BossData* bData = dynamic_cast<const BossData*>(data);
    CCLOG("Boss name: %s", bData->getName());
    CCLOG("Boss hp: %f", bData->getHP());
}