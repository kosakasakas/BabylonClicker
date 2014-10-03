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
    virtual void summon(Node* parent);
    void attack();
    void onAction();
    bool isHoldingNode() const;
    virtual void dump() const;
    bool canSummon() const;
    CC_SYNTHESIZE_READONLY(Node*, unitNode, UnitNode);
protected:
    bool canSacrificeAt(int slotID) const;
    void sacrificeAt(int slotID);
    void updateAttack();
    bool isEdge();
    virtual void initUnitNode();
};

#endif /* defined(__BabylonClicker__Unit__) */
