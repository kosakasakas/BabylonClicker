//
//  ScrollComponentCreator.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#ifndef __BabylonClicker__ScrollComponentCreator__
#define __BabylonClicker__ScrollComponentCreator__

#include <iostream>
#include "BaseObject.h"
#include "UnitData.h"

class ScrollComponentCreator : public BaseObject {
public:
    static Array* make();
    static Size* getComponentSize();
private:
    static Node* createComponent(UnitData* ud);
    static Sprite* createMagicIconSprite(const char* magic);
};

#endif /* defined(__BabylonClicker__ScrollComponentCreator__) */
