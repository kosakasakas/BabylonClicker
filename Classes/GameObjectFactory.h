//
//  GameObjectFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__GameObjectFactory__
#define __BabylonClicker__GameObjectFactory__

#include <iostream>
#include "GameObject.h"

class GameObjectFactory
{
public:
    GameObjectFactory();
    ~GameObjectFactory();
    GameObject* create();
protected:
    virtual GameObject* createObject() = 0;
};

#endif /* defined(__BabylonClicker__GameObjectFactory__) */
