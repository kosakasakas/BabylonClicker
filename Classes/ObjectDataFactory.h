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
#include "UCPlistLoader.h"

USING_NS_CC;

class ObjectDataFactory : public virtual BaseObject {
public:
    ObjectDataFactory(const char* filePath);
    virtual ~ObjectDataFactory();
    //CC_SYNTHESIZE_READONLY(Dictionary*, dictionary, Ditctionary);
    virtual void dump() const;
    void dumpPropertyValueAtIndex(int index) const;
    int getPropertyNum() const;
    int getObjectNum() const;
    Array* getPropertyArray() const;
    Dictionary* getPropertyValueAtIndex(int index) const;
    ObjectData* create(int index);
    Dictionary* getDictionary();
protected:
    virtual ObjectData* createObjectData(int index);
    UCPlistLoader* _ucPlistLoader;
};

#endif /* defined(__BabylonClicker__ObjectDataFactory__) */
