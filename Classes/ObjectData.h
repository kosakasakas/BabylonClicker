//
//  ObjectData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__ObjectData__
#define __BabylonClicker__ObjectData__

#include <iostream>
#include "BaseObject.h"
#include "cocos2d.h"

USING_NS_CC;

class ObjectData : public BaseObject {
public:
    ObjectData(Dictionary* data);
    ~ObjectData();
    CC_SYNTHESIZE_READONLY(Dictionary*, objData, ObjData);
    int getCost();
    int getLevel();
    int getObjectID();
    const char* getName();
    const char* getDescription();
    virtual void dump();
    void setCost(int value);
    void setLevel(int value);
    int getIntValue(const char* key);
    const char* getCharValue(const char* key);
    float getFloatValue(const char* key);
    void setIntValue(int val, const char* key);
    void setFloatValue(float val, const char* key);
    void setCharValue(const char* val, const char* key);
    
protected:
    static const char* COST_KEY;
    static const char* LEVEL_KEY;
    static const char* OBJECTID_KEY;
    static const char* NAME_KEY;
    static const char* DESCRIPTION_KEY;
};

#endif /* defined(__BabylonClicker__ObjectData__) */
