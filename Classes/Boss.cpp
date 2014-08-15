//
//  Boss.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Boss.h"

Boss::Boss(BossData* data)
: Unit(data)
{
}

Boss::~Boss()
{
}

const char* Boss::say() {
    return "Im boss. haha!";
}

void Boss::damage(float val) {
    data->reduceHP(val);
}