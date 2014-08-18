//
//  Observer.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef BabylonClicker_Observer_h
#define BabylonClicker_Observer_h

#include <iostream>
#include "ObjectData.h"
#include "BaseObject.h"

class Observer : public BaseObject {
public:
    Observer(){};
    virtual ~Observer(){};
    virtual void update(const ObjectData* data) = 0;
};

#endif
