//
//  UnitFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__UnitFactory__
#define __BabylonClicker__UnitFactory__

#include <iostream>
#include "GameObjectFactory.h"

class UnitFactory : public GameObjectFactory
{
public:
    UnitFactory();
    virtual ~UnitFactory();
protected:
    virtual GameObject* createObject(int ObjectID);
};

#endif /* defined(__BabylonClicker__UnitFactory__) */
