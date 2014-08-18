//
//  UnitData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__UnitData__
#define __BabylonClicker__UnitData__

#include <iostream>
#include "ObjectData.h"

class UnitData : public ObjectData {
public:
    UnitData(Dictionary* data);
    virtual ~UnitData();
    float getAttack() const;
    float getInterval() const;
    virtual void dump() const;
protected:
    static const char* ATTACK_KEY;
    static const char* INTERVAL_KEY;
};

#endif /* defined(__BabylonClicker__UnitData__) */
