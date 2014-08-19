//
//  BossData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__BossData__
#define __BabylonClicker__BossData__

#include <iostream>
#include "UnitData.h"
#include "Subject.h"

class BossData : public UnitData, public Subject {
public:
    BossData(Dictionary* data);
    virtual ~BossData();
    float getHP() const;
    void reduceHP(float damage);
    virtual void dump() const;
    
protected:
    static const char* HP_KEY;
};

#endif /* defined(__BabylonClicker__BossData__) */
