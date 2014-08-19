//
//  FieldObject.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/18.
//
//

#ifndef __BabylonClicker__FieldObject__
#define __BabylonClicker__FieldObject__

#include <iostream>
#include "Subject.h"

class FieldObject : public Subject {
public:
    FieldObject();
    ~FieldObject();
    virtual void dump() const;
    CC_SYNTHESIZE(int, level, Level);
    void incrementLevel();
};

#endif /* defined(__BabylonClicker__FieldObject__) */
