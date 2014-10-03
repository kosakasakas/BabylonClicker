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
    defaultPoint = Point(0,0);
}

UnitNode::~UnitNode()
{
    this->removeFromParent();
    this->removeAllChildren();
}

void UnitNode::onScheduleUpdate(float delta) {
    if (unitRef != NULL && unitRef->retainCount() > 0) {
        unitRef->onAction();
    } else {
        CCLOG("node is not exist or already released.");
    }
}

void UnitNode::setDefaultPoint(Point pos) {
    defaultPoint = pos;
    this->setPosition(defaultPoint);
}

Point& UnitNode::getDefaultPoint() {
    return defaultPoint;
}