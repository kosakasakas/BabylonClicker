//
//  GameController.h
//  UnicornEngine
//
//  Created by Takahiro Kosaka on 2013/11/17.
//
//

#ifndef __UnicornEngine__GameController__
#define __UnicornEngine__GameController__

#include <iostream>
#include "cocos2d.h"
#include "UnitFactory.h"
#include "ItemFactory.h"
#include "MagicFactory.h"
#include "BossFactory.h"

class GameController
{
private:
    GameController();
    ~GameController();
    static GameController* _singleton;
public:
    static GameController* getInstance();
    CC_SYNTHESIZE_READONLY(UnitFactory*, unitFactory, UnitFactory);
    CC_SYNTHESIZE_READONLY(ItemFactory*, itemFactory, ItemFactory);
    CC_SYNTHESIZE_READONLY(MagicFactory*, magicFactory, MagicFactory);
    CC_SYNTHESIZE_READONLY(BossFactory*, bossFactory, BossFactory);
};

#endif /* defined(__UnicornEngine__GameController__) */
