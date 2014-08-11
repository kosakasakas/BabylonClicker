//
//  UCAnimation.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/11.
//
//

#include "UCAnimation.h"

Point UCAnimation::getRotatePoint(Point from, float distance, float degree) {
    float radian = CC_DEGREES_TO_RADIANS(degree);
    float x = distance * cos(radian);
    float y = distance * sin(radian);
    Point point = Point(from.x+x, from.y+y);
    return point;
}

ActionInterval* UCAnimation::getDamageAction(Point from) {
    int degree = arc4random()%360;
    int length = 5;
    Point destination = UCAnimation::getRotatePoint(from, length, degree);
    auto go = MoveTo::create(0.05f, destination);
    auto back = MoveTo::create(0.05f, from);
    Sequence* sequence = Sequence::create(go, back, NULL);
    auto blink = Blink::create(0.1f, 1);
    Spawn* spawn = Spawn::create(sequence,blink, NULL);
    return spawn;
}