//
//  ItemFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__ItemFactory__
#define __BabylonClicker__ItemFactory__

#include <iostream>
#include "GameObjectFactory.h"

class ItemFactory : public GameObjectFactory
{
public:
    ItemFactory();
    virtual ~ItemFactory();
protected:
    virtual GameObject* createObject(int objectID);
};

#endif /* defined(__BabylonClicker__ItemFactory__) */
