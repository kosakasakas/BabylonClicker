//
//  Item.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Item__
#define __BabylonClicker__Item__

#include <iostream>
#include "GameObject.h"

class Item : public GameObject
{
public:
    Item(ObjectData* data);
    virtual ~Item();
};

#endif /* defined(__BabylonClicker__Item__) */
