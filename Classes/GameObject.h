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
#include "BaseObject.h"
#include "ObjectData.h"

USING_NS_CC;

class GameObject : public virtual BaseObject
{
public:
    GameObject(ObjectData* data);
    virtual ~GameObject();
    CC_SYNTHESIZE_READONLY(ObjectData*, objectData, ObjectData);
    virtual bool canPurchase() const;
    virtual bool canSacrifice() const;
    virtual bool canSummon() const;
    virtual void purchase() const;
    virtual void sacrifice();
    virtual void summon();
    virtual void dump() const;
};

#endif /* defined(__BabylonClicker__GameObject__) */
