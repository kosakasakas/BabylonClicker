//
//  Utility.h
//  UnicornEngine
//
//  Created by Takahiro Kosaka on 2014/04/23.
//
//

#ifndef __UnicornEngine__Utility__
#define __UnicornEngine__Utility__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class Utility
{
private:
public:
    static bool isDecimalValue(const char* text);
    static const char* getStrFromFloatValue(float val);
    static int getRandomInt(int limit);
};

#endif /* defined(__UnicornEngine__Utility__) */
