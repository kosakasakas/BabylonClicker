//
//  UnitField.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/18.
//
//

#ifndef __BabylonClicker__UnitField__
#define __BabylonClicker__UnitField__

#include <iostream>
#include "FieldObject.h"
#include "UnitData.h"

class UnitField : public FieldObject {
public:
    UnitField();
    ~UnitField();
    virtual void dump() const;
    CC_SYNTHESIZE(int, unitNum, UnitNum);
    CC_SYNTHESIZE(UnitData*, sharedUnitData, SharedUnitData);
    void incrementUnitNum();
    bool isHoldingSharedUnitData() const;
};
#endif /* defined(__BabylonClicker__UnitField__) */
