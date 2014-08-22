//
//  Boss.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Boss__
#define __BabylonClicker__Boss__

#include <iostream>
#include "Unit.h"
#include "BossData.h"

class Boss : public Unit {
public:
    Boss(BossData* data, int level);
    virtual ~Boss();
    void damage(float val);
private:
    void onDestroyed();
};

#endif /* defined(__BabylonClicker__Boss__) */
