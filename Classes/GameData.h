//
//  GameData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__GameData__
#define __BabylonClicker__GameData__

#include <iostream>
#include "BaseObject.h"
#include "cocos2d.h"

USING_NS_CC;

class GameData : public BaseObject {
public:
    GameData(const char* filePath);
    ~GameData();
    CC_SYNTHESIZE_READONLY(Dictionary*, dictionary, Ditctionary);
    virtual void dump();
    void dumpPropertyValueAtIndex(int index);
    int getPropertyNum();
    int getObjectNum();
    Array* getPropertyArray();
    Dictionary* getPropertyValueAtIndex(int index);
};

#endif /* defined(__BabylonClicker__GameData__) */
