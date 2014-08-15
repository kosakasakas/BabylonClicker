//
//  ObjectDataFactory.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__ObjectDataFactory__
#define __BabylonClicker__ObjectDataFactory__

#include <iostream>
#include "BaseObject.h"
#include "cocos2d.h"
#include "ObjectData.h"

USING_NS_CC;

class ObjectDataFactory : public BaseObject {
public:
    ObjectDataFactory(const char* filePath);
    virtual ~ObjectDataFactory();
    CC_SYNTHESIZE_READONLY(Dictionary*, dictionary, Ditctionary);
    virtual void dump();
    void dumpPropertyValueAtIndex(int index);
    int getPropertyNum();
    int getObjectNum();
    Array* getPropertyArray();
    Dictionary* getPropertyValueAtIndex(int index);
    ObjectData* create(int index);
protected:
    virtual ObjectData* createObjectData(int index) = 0;
};

#endif /* defined(__BabylonClicker__ObjectDataFactory__) */
