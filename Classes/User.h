//
//  User.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__User__
#define __BabylonClicker__User__

#include <iostream>
#include "cocos2d.h"
#include "BaseObject.h"

class User : public BaseObject {
public:
    User();
    ~User();
    CC_SYNTHESIZE(int, soul, Soul);
    virtual void dump();
    void addSoul(int soul);
    void reduceSoul(int soul);
};
#endif /* defined(__BabylonClicker__User__) */
