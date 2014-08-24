//
//  UnitNodeCriticalDecorator.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/23.
//
//

#ifndef __BabylonClicker__UnitNodeCriticalDecorator__
#define __BabylonClicker__UnitNodeCriticalDecorator__

#include <iostream>
#include "UnitNode.h"
#include "Observer.h"

class UnitNodeCriticalDecorator : public UnitNode, public Observer {
public:
    UnitNodeCriticalDecorator( UnitNode* uNode);
    virtual ~UnitNodeCriticalDecorator();
    virtual void onScheduleUpdate(float delta);
    CC_SYNTHESIZE_READONLY(UnitNode*, unitNode, UnitNode);
    virtual void updateStatus(const BaseObject* data);
protected:
    float myCriticalLot;
    bool isCritical;
    bool checkCritical(float criticalLot);
};

#endif /* defined(__BabylonClicker__UnitNodeCriticalDecorator__) */
