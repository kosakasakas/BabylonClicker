//
//  CriticalNode.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#include "CriticalNode.h"

CriticalNode::CriticalNode()
{
    generateCriticalLot();
}

CriticalNode::~CriticalNode()
{
}

void CriticalNode::onScheduleUpdate(float delta) {
    generateCriticalLot();
    CCLOG("generate critical lot: %f", getCriticalLot());
}

void CriticalNode::generateCriticalLot() {
    int num = arc4random()%10000;
    criticalLot = (float)num/100.f;
}