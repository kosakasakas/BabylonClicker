//
//  CriticalSubjectNode.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#include "CriticalSubjectNode.h"
#include "Utility.h"

CriticalSubjectNode::CriticalSubjectNode()
{
    criticalLot = generateCriticalLot();
    subject = new Subject();
}

CriticalSubjectNode::~CriticalSubjectNode()
{
    subject->release();
}

void CriticalSubjectNode::onUpdateCriticalLot(float delta) {
    CCLOG("notify critical observers.");
    criticalLot = generateCriticalLot();
    notifyObservers();
}

float CriticalSubjectNode::generateCriticalLot() {
    int num = Utility::getRandomInt(10000);
    return (float)num/100.f;
}

void CriticalSubjectNode::registerObserver(Observer* o) {
    subject->registerObserver(o);
}

void CriticalSubjectNode::removeObserver(Observer* o) {
    subject->removeObserver(o);
}

void CriticalSubjectNode::notifyObservers() const {
    subject->notifyObservers();
}
