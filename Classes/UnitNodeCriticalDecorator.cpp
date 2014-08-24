//
//  UnitNodeCriticalDecorator.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/23.
//
//

#include "UnitNodeCriticalDecorator.h"
#include "CriticalSubjectNode.h"
#include "GameController.h"
#include "BattleController.h"

UnitNodeCriticalDecorator::UnitNodeCriticalDecorator( UnitNode* uNode )
: UnitNode(uNode->getUnitRef())
, isCritical(false)
{
    unitNode = uNode;
    int num = arc4random_uniform(10000);
    myCriticalLot = (float)num/100.f;
    UnitData* uData = (UnitData*)unitRef->getObjectData();
    this->schedule(schedule_selector(UnitNode::onScheduleUpdate), uData->getInterval());
}

UnitNodeCriticalDecorator::~UnitNodeCriticalDecorator()
{
    this->unscheduleAllSelectors();
    unitNode->release();
}

void UnitNodeCriticalDecorator::onScheduleUpdate(float delta) {
    if (unitNode != NULL) {
        unitNode->onScheduleUpdate(delta);
    }
}

void UnitNodeCriticalDecorator::updateStatus(const BaseObject* data) {
    if(unitNode == NULL) {
        return;
    }
    
    float criticalLot = BattleController::getInstance()->getCritical()->getCriticalLot();
    /*const CriticalSubjectNode* csn = dynamic_cast<const CriticalSubjectNode*>(data);
    bool isCriticalNew = checkCritical(csn->getCriticalLot());*/
    bool isCriticalNew = checkCritical(criticalLot);
    UnitData* uData = (UnitData*)unitRef->getObjectData();
    if (!isCritical && isCriticalNew) { // on critical
        this->unscheduleAllSelectors();
        float criticalInterval = GameController::getInstance()->getConfig()->getAttackInterval();
        this->schedule(schedule_selector(UnitNode::onScheduleUpdate), criticalInterval);
        isCritical = true;
        CCLOG("%s 's critical time start now!!", uData->getName());
        return;
    } else if (isCritical && !isCriticalNew) { // off critical
        this->unscheduleAllSelectors();
        float interval = uData->getInterval();
        this->schedule(schedule_selector(UnitNode::onScheduleUpdate), interval);
        isCritical = false;
        CCLOG("%s 's critical time stop now..", uData->getName());
        return;
    }
    return;
}

bool UnitNodeCriticalDecorator::checkCritical(float criticalLot) {
    if (unitNode == NULL) {
        return false;
    }
    
    UnitData* ud = (UnitData*)unitNode->getUnitRef()->getObjectData();
    float length = ud->getCriticalLength();
    float dis = criticalLot - myCriticalLot;
    if (dis*dis <= length*length) {
        CCLOG("%s 's criticalLot: %f criticalLot: %f", ud->getName(), myCriticalLot, criticalLot);
        return true;
    }
    return false;
}