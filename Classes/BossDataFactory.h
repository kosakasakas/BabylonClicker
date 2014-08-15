//
//  BossDataFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__BossDataFactory__
#define __BabylonClicker__BossDataFactory__

#include <iostream>
#include "UnitDataFactory.h"

class BossDataFactory : public UnitDataFactory {
public:
    BossDataFactory(const char* filePath);
    virtual ~BossDataFactory();
protected:
    virtual ObjectData* createObjectData(int index);
};

#endif /* defined(__BabylonClicker__BossDataFactory__) */
