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
    float getDefaultHP() const;
    float getHpGrowth() const;
    float getLotWeight() const;
    void reduceHP(float damage);
    void updateHP();
    virtual void dump() const;
    CC_SYNTHESIZE(float, hp, HP);
    
protected:
    virtual void update();
    static const char* HP_KEY;
    static const char* HP_GROWTH_KEY;
    static const char* LOT_WEIGHT_KEY;
};

#endif /* defined(__BabylonClicker__BossData__) */
