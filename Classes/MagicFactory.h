//
//  MagicFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__MagicFactory__
#define __BabylonClicker__MagicFactory__

#include <iostream>
#include "GameObjectFactory.h"

class MagicFactory : public GameObjectFactory
{
public:
    MagicFactory();
    ~MagicFactory();
protected:
    virtual GameObject* createObject();
};

#endif /* defined(__BabylonClicker__MagicFactory__) */
