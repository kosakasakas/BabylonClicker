//
//  UnicornPlistLoader.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#ifndef __BabylonClicker__UnicornPlistLoader__
#define __BabylonClicker__UnicornPlistLoader__

#include "cocos2d.h"

USING_NS_CC;

class UnicornPlistLoader {
public:
    UnicornPlistLoader(const char* filePath);
    virtual ~UnicornPlistLoader();
    Dictionary* getPropertyValueAtIndex(int index) const;
    int getObjectNum() const;
    int getPropertyNum() const;
    Array* getPropertyArray() const;
    void dumpPropertyValueAtIndex(int index) const;
    void dump() const;
    CC_SYNTHESIZE_READONLY(Dictionary*, dictionary, Dictionary);
};

#endif /* defined(__BabylonClicker__UnicornPlistLoader__) */
