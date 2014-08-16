
//
//  BossData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "BossData.h"

const char* BossData::HP_KEY = "hp";

BossData::BossData(Dictionary* data)
:UnitData(data)
{
    observers = Array::create();
}

BossData::~BossData()
{
    observers->release();
}

float BossData::getHP() {
    return getFloatValue(HP_KEY);
}

void BossData::reduceHP(float damage) {
    float hp = getHP();
    setFloatValue(hp - damage, HP_KEY);
    notifyObservers();
}

void BossData::dump() {
    UnitData::dump();
    CCLOG("hp: %f", getHP());
}

void BossData::registerObserver(Observer* o) {
    observers->addObject(o);
}

void BossData::removeObserver(Observer* o) {
    observers->removeObject(o);
}

void BossData::notifyObservers() {
    CCLOG("notify BossData observers!!");
    Object* it;
    CCARRAY_FOREACH(observers, it)
    {
        Observer* o = dynamic_cast<Observer*>(it);
        o->update(this);
    }
}