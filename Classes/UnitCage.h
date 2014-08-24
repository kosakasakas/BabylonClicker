//
//  UnitCage.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__UnitCage__
#define __BabylonClicker__UnitCage__

#include <iostream>
#include "cocos2d.h"
#include "Unit.h"
#include "BaseObject.h"

USING_NS_CC;

class UnitCage : public virtual BaseObject {
public:
    UnitCage(int unitNum);
    virtual ~UnitCage();
    CC_SYNTHESIZE_READONLY(int, maxUnitNum, MaxUnitNum);
    CC_SYNTHESIZE(Array*, unitArray, UnitArray);
    bool canAddUnit() const;
    void addUnit(Unit* unit);
    void removeUnit(Unit* unit);
    virtual void dump() const;
    void attackAll();
};

#endif /* defined(__BabylonClicker__UnitCage__) */
