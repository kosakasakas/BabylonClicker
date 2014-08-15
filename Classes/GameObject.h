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
#include "ObjectData.h"

USING_NS_CC;

class GameObject : public BaseObject
{
public:
    GameObject(ObjectData* data);
    virtual ~GameObject();
    virtual const char* say() = 0;
    CC_SYNTHESIZE_READONLY(ObjectData*, objectData, ObjectData);
    virtual bool canPurchase();
    virtual bool canSacrifice();
    virtual bool canSummon();
    virtual void purchase();
    virtual void sacrifice();
    virtual void summon();
    virtual void dump();
};

#endif /* defined(__BabylonClicker__GameObject__) */
