//
//  Boss.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Boss.h"
#include "BattleController.h"
#include "UCAnimation.h"

Boss::Boss(BossData* data, int level)
: Unit(data)
{
    bossDataDisplay = new BossDataDisplay();
    bossDataDisplay->retain();
    data->registerObserver(bossDataDisplay);
    ((BossData*)objectData)->setLevel(level);
}

Boss::~Boss()
{
}

void Boss::initUnitNode() {
    unitNode = new UnitNode(this);
}

void Boss::damage(float val) {
    BossData* bData = (BossData*)objectData;
    (bData)->reduceHP(val);
    
    // damage action.
    auto node = getUnitNode();
    if (node && node->isVisible()) {
        node->stopAllActions();
        node->runAction(UCAnimation::getDamageAction(node->getDefaultPoint()));
    }
    
    if (bData->getHP() <= 0) {
        onDestroyed();
    }
}

void Boss::onDestroyed() {
    CCLOG("Boss is destroyed..");
    BattleController* bc = BattleController::getInstance();
    int currentLevel = objectData->getLevel();
    bc->getField()->setBossLevel(objectData->getObjectID(), ++currentLevel);
    bc->onTargetBossDestroyed();
}

void Boss::summon(Node* parent) {
    initUnitNode();
    
    auto unitSprite = Sprite::create(objectData->getSpriteFilePath().c_str());
    auto unitNode = getUnitNode();
    unitNode->addChild(unitSprite);
    parent->addChild(unitNode);
}