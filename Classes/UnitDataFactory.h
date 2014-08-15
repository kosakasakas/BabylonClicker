//
//  UnitDataFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__UnitDataFactory__
#define __BabylonClicker__UnitDataFactory__

#include <iostream>
#include "ObjectDataFactory.h"

class UnitDataFactory : public ObjectDataFactory {
public:
    UnitDataFactory(const char* filePath);
    ~UnitDataFactory();
protected:
    virtual ObjectData* createObjectData(int index);
};

#endif /* defined(__BabylonClicker__UnitDataFactory__) */
