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
    ~ItemFactory();
protected:
    virtual GameObject* createObject();
};

#endif /* defined(__BabylonClicker__ItemFactory__) */
