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
#include "UnitData.h"

class Unit : public GameObject
{
public:
    Unit(UnitData* data);
    virtual ~Unit();
    virtual const char* say();
    virtual void summon();
    virtual bool canSummon();
};

#endif /* defined(__BabylonClicker__Unit__) */
