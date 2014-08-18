//
//  UnitNode.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/17.
//
//

#include "UnitNode.h"

UnitNode::UnitNode(Unit* u)
: unitRef(u)
{
    //UnitData* uData = (UnitData*)u->getObjectData();
    //this->schedule(schedule_selector(UnitNode::onScheduleUpdate), uData->getInterval());
}

UnitNode::~UnitNode()
{
    //this->unscheduleAllSelectors();
}

void UnitNode::onScheduleUpdate(float delta) {
    if (unitRef != NULL && unitRef->retainCount() > 0) {
        unitRef->onAction();
    } else {
        CCLOG("node is not exist or already released.");
    }
}