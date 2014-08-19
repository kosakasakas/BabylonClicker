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
#include "BaseObject.h"

class Observer : virtual public BaseObject {
public:
    Observer(){};
    virtual ~Observer(){};
    virtual void updateStatus(const BaseObject* data) = 0;
};

#endif
