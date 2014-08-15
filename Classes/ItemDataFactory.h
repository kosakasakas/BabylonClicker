//
//  ItemDataFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__ItemDataFactory__
#define __BabylonClicker__ItemDataFactory__

#include <iostream>
#include "ObjectDataFactory.h"

class ItemDataFactory : public ObjectDataFactory {
public:
    ItemDataFactory(const char* filePath);
    virtual ~ItemDataFactory();
protected:
    virtual ObjectData* createObjectData(int index);
};

#endif /* defined(__BabylonClicker__ItemDataFactory__) */
