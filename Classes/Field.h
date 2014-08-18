//
//  Field.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Field__
#define __BabylonClicker__Field__

#include <iostream>
#include "cocos2d.h"
#include "BaseObject.h"

class Field : public BaseObject {
public:
    Field();
    virtual ~Field();
    CC_SYNTHESIZE(float, babylonOffset, BabylonOffset);
    CC_SYNTHESIZE(float, marikaOffset, MarikaOffset);
    CC_SYNTHESIZE(float, hanaarukiOffset, HanaarukiOffset);
    virtual void dump() const;
};
#endif /* defined(__BabylonClicker__Field__) */
