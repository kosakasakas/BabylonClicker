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
#include "cocos2d.h"
#include "Observer.h"

USING_NS_CC;

class ObjectData : public Observer {
public:
    ObjectData(Dictionary* data);
    virtual ~ObjectData();
    CC_SYNTHESIZE_READONLY(Dictionary*, objData, ObjData);
    int getCost() const;
    int getLevel() const;
    int getObjectID() const;
    const char* getName() const;
    const char* getDescription() const;
    virtual void dump() const;
    void setCost(int value);
    void setLevel(int value);
    int getIntValue(const char* key) const;
    const char* getCharValue(const char* key) const;
    float getFloatValue(const char* key) const;
    void setIntValue(int val, const char* key);
    void setFloatValue(float val, const char* key);
    void setCharValue(const char* val, const char* key);
    virtual void updateStatus(const BaseObject* data);
    
protected:
    static const char* COST_KEY;
    static const char* LEVEL_KEY;
    static const char* OBJECTID_KEY;
    static const char* NAME_KEY;
    static const char* DESCRIPTION_KEY;
};

#endif /* defined(__BabylonClicker__ObjectData__) */
