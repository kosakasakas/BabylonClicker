//
//  BossFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__BossFactory__
#define __BabylonClicker__BossFactory__

#include <iostream>
#include "GameObjectFactory.h"

class BossFactory : public GameObjectFactory {
public:
    BossFactory();
    virtual ~BossFactory();
protected:
    virtual GameObject* createObject(int objectID);
};

#endif /* defined(__BabylonClicker__BossFactory__) */
