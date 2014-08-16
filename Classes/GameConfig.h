//
//  GameConfig.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__GameConfig__
#define __BabylonClicker__GameConfig__

#include <iostream>
#include "ObjectData.h"
#include "BaseObject.h"

class GameConfig : public BaseObject {
public:
    GameConfig();
    virtual ~GameConfig();
    int getAttackInterval();
    int getMaxUnitNum();
    const char* getNendSpotID();
    const char* getNendApiKey();
    virtual void dump();
private:
    ObjectData* data;
};

#endif /* defined(__BabylonClicker__GameConfig__) */
