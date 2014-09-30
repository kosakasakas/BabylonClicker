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
    CC_SYNTHESIZE_READONLY(float, cost, Cost);
    CC_SYNTHESIZE_READONLY(int, level, Level);
    int getObjectID() const;
    const char* getGrade() const;
    const char* getName() const;
    const char* getDescription() const;
    virtual void dump() const;
    void incrementLevel();
    void reduceLevel(int value);
    float getDefaultCost() const;
    int getIntValue(const char* key) const;
    const char* getCharValue(const char* key) const;
    float getFloatValue(const char* key) const;
    void setIntValue(int val, const char* key);
    void setFloatValue(float val, const char* key);
    void setCharValue(const char* val, const char* key);
    virtual void updateStatus(const BaseObject* data);
    void setLevel(int inputLevel);
    std::string getSpriteFilePath();
    std::string getMiniSpriteFilePath();
    
protected:
    void updateCost();
    virtual void update();
    static const char* COST_KEY;
    static const char* OBJECTID_KEY;
    static const char* NAME_KEY;
    static const char* DESCRIPTION_KEY;
    static const char* COST_GROWTH_KEY;
    std::string getSpriteFileString();
    virtual const char* getObjectType() const = 0;
};

#endif /* defined(__BabylonClicker__ObjectData__) */
