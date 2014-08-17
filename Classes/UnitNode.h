//
//  UnitNode.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/17.
//
//

#ifndef __BabylonClicker__UnitNode__
#define __BabylonClicker__UnitNode__

#include <iostream>
#include "cocos2d.h"
#include "Unit.h"

USING_NS_CC;

class UnitNode : public Node {
public:
    UnitNode(Unit* u);
    virtual ~UnitNode();
    virtual void onScheduleUpdate(float delta);
protected:
    Unit* unitRef;
};

#endif /* defined(__BabylonClicker__UnitNode__) */
