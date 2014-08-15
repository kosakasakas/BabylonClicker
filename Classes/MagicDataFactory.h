//
//  MagicDataFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__MagicDataFactory__
#define __BabylonClicker__MagicDataFactory__

#include <iostream>
#include "ObjectDataFactory.h"

class MagicDataFactory : public ObjectDataFactory {
public:
    MagicDataFactory(const char* filePath);
    ~MagicDataFactory();
protected:
    virtual ObjectData* createObjectData(int index);
};
#endif /* defined(__BabylonClicker__MagicDataFactory__) */
