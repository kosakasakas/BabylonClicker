//
//  Boss.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Boss__
#define __BabylonClicker__Boss__

#include <iostream>
#include "Unit.h"

class Boss : public Unit {
public:
    Boss();
    ~Boss();
    virtual const char* say();
};

#endif /* defined(__BabylonClicker__Boss__) */
