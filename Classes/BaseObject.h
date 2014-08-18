//
//  BaseObject.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__BaseObject__
#define __BabylonClicker__BaseObject__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class BaseObject : public Object {
public:
    BaseObject();
    ~BaseObject();
    virtual void dump() const;
};

#endif /* defined(__BabylonClicker__BaseObject__) */
