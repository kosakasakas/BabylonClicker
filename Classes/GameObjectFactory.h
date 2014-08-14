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
#include "cocos2d.h"
#include "GameObject.h"

class GameObjectFactory : public cocos2d::Object
{
public:
    GameObjectFactory();
    ~GameObjectFactory();
    virtual GameObject* create();
protected:
    virtual GameObject* createObject() = 0;
};

#endif /* defined(__BabylonClicker__GameObjectFactory__) */
