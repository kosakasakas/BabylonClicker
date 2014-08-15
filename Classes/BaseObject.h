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

class BaseObject {
public:
    BaseObject();
    ~BaseObject();
    virtual void dump();
};

#endif /* defined(__BabylonClicker__BaseObject__) */
