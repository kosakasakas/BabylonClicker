//
//  Subject.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__Subject__
#define __BabylonClicker__Subject__

#include <iostream>
#include "Observer.h"

class Subject {
public:
    Subject(){};
    virtual ~Subject(){};
    virtual void registerObserver(Observer* o)=0;
    virtual void removeObserver(Observer* o)=0;
    virtual void notifyObservers()=0;
};

#endif /* defined(__BabylonClicker__Subject__) */
