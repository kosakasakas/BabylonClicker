//
//  Unit.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Unit__
#define __BabylonClicker__Unit__

#include <iostream>
#include "GameObject.h"

class Unit : public GameObject
{
public:
    Unit();
    ~Unit();
    virtual const char* say();
};

#endif /* defined(__BabylonClicker__Unit__) */
