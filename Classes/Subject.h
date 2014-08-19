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

class Subject : virtual public BaseObject {
public:
    Subject();
    virtual ~Subject();
    virtual void registerObserver(Observer* o);
    virtual void removeObserver(Observer* o);
    virtual void notifyObservers() const;
    virtual bool hasObserver(Observer* o);
protected:
    Array* observers;
};

#endif /* defined(__BabylonClicker__Subject__) */
