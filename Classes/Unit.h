//
//  Unit.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Unit__
#define __BabylonClicker__Unit__

#include <iostream>
#include "GameObject.h"
#include "UnitData.h"

class Unit : public GameObject
{
public:
    Unit(UnitData* data);
    virtual ~Unit();
    virtual void summon();
    void attack();
    void onAction();
    CC_SYNTHESIZE(Node*, unitNode, UnitNode);
    bool isHoldingNode() const;
    virtual void dump() const;
    bool canSummon() const;
protected:
    bool canSummonAt(int slotID) const;
};

#endif /* defined(__BabylonClicker__Unit__) */
