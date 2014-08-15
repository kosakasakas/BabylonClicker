//
//  Iterator.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__Iterator__
#define __BabylonClicker__Iterator__

#include <iostream>
#include "BaseObject.h"

class Iterator {
public:
    Iterator() {
    };
    virtual ~Iterator() {
    };
    virtual bool hasNext() = 0;
    virtual BaseObject* next() = 0;
};

#endif /* defined(__BabylonClicker__Iterator__) */
