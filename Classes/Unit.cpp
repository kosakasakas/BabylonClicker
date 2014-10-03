//
//  Unit.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Unit.h"
#include "BattleController.h"
#include "UnitNode.h"
#include "UnitNodeCriticalDecorator.h"
#include "UCAnimation.h"
#include "ComponentCreator.h"

Unit::Unit(UnitData* data)
: GameObject(data)
{
}

Unit::~Unit()
{
    if (unitNode) {
        unitNode->removeFromParent();
        unitNode->removeAllChildren();
        unitNode->release();
    }
}

void Unit::initUnitNode() {
    // Notice: スケジューラ登録はUnitNodeCriticalDecoratorでやります
    unitNode = new UnitNodeCriticalDecorator(new UnitNode(this));
}

void Unit::summon(Node* parent) {
    // add node.
    initUnitNode();
    
    UnitCage* uc = BattleController::getInstance()->getActiveUnitCage();
    if (!canPurchase() || !canSacrifice() || !uc->canAddUnit()) {
        CCLOG("%s can not summon!!", getObjectData()->getName());
        return;
    }
    
    for(int i=0; i<UnitData::SACRIFICE_SLOT_NUM; ++i) {
        sacrificeAt(i);
    }
    uc->addUnit(this);
    purchase();
    CCLOG("%s is summoned.", getObjectData()->getName());
    objectData->incrementLevel();
    
    auto unitSprite = Sprite::create(objectData->getSpriteFilePath().c_str());
    unitNode->addChild(unitSprite);
    parent->addChild(unitNode);
}

bool Unit::canSummon() const {
    for(int i=0; i<UnitData::SACRIFICE_SLOT_NUM; ++i) {
        if (!canSacrificeAt(i)) {
            return false;
        }
    }
    return true;
}

bool Unit::canSacrificeAt(int slotID) const{
    if (0>slotID || slotID>UnitData::SACRIFICE_SLOT_NUM) {
        return false;
    }
    UnitData* ud = (UnitData*)objectData;
    int sf = ud->getSacrifice(slotID);
    if (sf == -1) {
        return true;
    }
    else if (sf >= 0) {
        int sfn = ud->getSacrificeNum(slotID);
        Field* fd = BattleController::getInstance()->getField();
        int havingSfn = fd->getSharedUnitData(sf)->getUnitNum();
        if (havingSfn >= sfn) {
            return true;
        }
    }
    return false;
}

void Unit::sacrificeAt(int slotID) {
    if (0>slotID || slotID>UnitData::SACRIFICE_SLOT_NUM || !canSacrificeAt(slotID)) {
        CCLOG("cannot cacrifice at slotID: %d", slotID);
        return;
    }
    UnitData* ud = (UnitData*)objectData;
    int sf = ud->getSacrifice(slotID);
    if (sf == -1) {
        return;
    }
    else if (sf >= 0) {
        int sfn = ud->getSacrificeNum(slotID);
        Array* unitRef = BattleController::getInstance()->getField()->getUnitRefArray(sf);
        UnitCage* uc = BattleController::getInstance()->getActiveUnitCage();
        for (int i=0; i<sfn; ++i) {
            Unit* sacrificeUnit = dynamic_cast<Unit*>(unitRef->getObjectAtIndex(0));
            uc->removeUnit(sacrificeUnit);
        }
    }
}

void Unit::attack() {
    UnitData* uData = (UnitData*)objectData;
    CCLOG("Attacker name: %s", uData->getName());
    CCLOG("Attacker power: %f", uData->getAttack());
    float attack = uData->getAttack();
    if(isEdge()) {
        float magicOffset = BattleController::getInstance()->getConfig()->getMagicOffsetRate();
        attack *= magicOffset;
    }
    auto boss = BattleController::getInstance()->getTargetBoss();
    if (boss == NULL) return;
    boss->damage(attack);
    
    // attack anim.
    if(unitNode && unitNode->isVisible()) {
        unitNode->stopAllActions();
        unitNode->runAction(UCAnimation::getAttackAction(unitNode->getDefaultPoint(), ComponentCreator::bossPosition));
    }
}

void Unit::onAction() {
    CCLOG("Unit onAction called");
    attack();
}

bool Unit::isHoldingNode() const{
    return (unitNode != NULL) ? true : false;
}

bool Unit::isEdge() {
    Boss* boss = BattleController::getInstance()->getTargetBoss();
    BossData* bData = (BossData*)boss->getObjectData();
    UnitData* uData = (UnitData*)objectData;
    Field::MagicFieldType bMagic = Field::getMagicFieldType(bData->getMagic());
    Field::MagicFieldType uMagic = Field::getMagicFieldType(uData->getMagic());
    return Field::isEdge(uMagic, bMagic);
}

void Unit::dump() const{
    ((UnitData*)objectData)->dump();
    CCLOG("unitData RetainCount: %d", objectData->retainCount());
    CCLOG("unitNode RetainCount: %d", unitNode->retainCount());
    CCLOG("isHoldingNode: %d", isHoldingNode());
}