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

class GameConfig : public virtual BaseObject {
public:
    GameConfig();
    virtual ~GameConfig();
    float getAttackInterval() const;
    int getMaxUnitNum() const;
    const char* getNendSpotID() const;
    const char* getNendApiKey() const;
    float getMagicOffsetRate() const;
    float getCriticalInterval() const;
    virtual void dump() const;
private:
    ObjectData* data;
};

#endif /* defined(__BabylonClicker__GameConfig__) */
