//
//  RandomBossFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#ifndef __BabylonClicker__RandomBossFactory__
#define __BabylonClicker__RandomBossFactory__

#include <iostream>
#include "BaseObject.h"
#include "BossFactory.h"
#include "Boss.h"

class RandomBossFactory : public BaseObject {
public:
    RandomBossFactory();
    virtual ~RandomBossFactory();
    Boss* create();
private:
    BossFactory* bossFactory;
    float getRandomNum();
};

#endif /* defined(__BabylonClicker__RandomBossFactory__) */
