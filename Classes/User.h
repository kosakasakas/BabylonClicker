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
#include "Subject.h"

class User : public Subject {
public:
    User();
    virtual ~User();
    CC_SYNTHESIZE(float, soul, Soul);
    virtual void dump() const;
    void addSoul(float soul);
    void reduceSoul(float soul);
};
#endif /* defined(__BabylonClicker__User__) */
