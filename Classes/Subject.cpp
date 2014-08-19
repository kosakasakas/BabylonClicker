//
//  Subject.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#include "Subject.h"

Subject::Subject()
{
    observers = Array::create();
    observers->retain();
}

Subject::~Subject()
{
    observers->release();
}

void Subject::registerObserver(Observer* o) {
    observers->addObject(o);
}

void Subject::removeObserver(Observer* o) {
    observers->removeObject(o);
}

void Subject::notifyObservers() const {
    CCLOG("notify observers!!");
    Object* it;
    CCARRAY_FOREACH(observers, it)
    {
        Observer* o = dynamic_cast<Observer*>(it);
        o->updateStatus(this);
    }
}

bool Subject::hasObserver(Observer* o) {
    return observers->containsObject(o);
}