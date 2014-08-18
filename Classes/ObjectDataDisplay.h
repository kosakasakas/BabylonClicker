//
//  ObjectDataDisplay.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__ObjectDataDisplay__
#define __BabylonClicker__ObjectDataDisplay__

#include <iostream>
#include "Observer.h"

class ObjectDataDisplay : public Observer {
public:
    ObjectDataDisplay(){};
    virtual ~ObjectDataDisplay(){};
    virtual void update(const ObjectData* data) = 0;
    virtual void draw(const ObjectData* data) = 0;
};

#endif /* defined(__BabylonClicker__ObjectDataDisplay__) */
