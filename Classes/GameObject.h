//
//  GameObject.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__GameObject__
#define __BabylonClicker__GameObject__

#include <iostream>
#include "cocos2d.h"
#include "BaseObject.h"

USING_NS_CC;

class GameObject : public cocos2d::Object, public BaseObject
{
public:
    GameObject();
    ~GameObject();
    virtual const char* say() = 0;
    CC_SYNTHESIZE_READONLY(int, cost, Cost);
    CC_SYNTHESIZE_READONLY(int, level, level);
    CC_SYNTHESIZE_READONLY(int, objectID, ObjectID);
    CC_SYNTHESIZE_READONLY(Dictionary*, objectData, ObjectData);
    virtual bool canPurchase();
    virtual bool canSacrifice();
    virtual bool canSummon();
    virtual void purchase();
    virtual void sacrifice();
    virtual void summon();
    virtual void dump();
};

#endif /* defined(__BabylonClicker__GameObject__) */
