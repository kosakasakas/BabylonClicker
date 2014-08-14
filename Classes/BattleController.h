//
//  BattleController.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__BattleController__
#define __BabylonClicker__BattleController__

#include <iostream>
#include "cocos2d.h"
#include "Boss.h"

class BattleController
{
private:
    BattleController();
    ~BattleController();
    static BattleController* _singleton;
public:
    static BattleController* getInstance();
    CC_SYNTHESIZE(Boss*, targetBoss, TargetBoss);
};

#endif /* defined(__BabylonClicker__BattleController__) */
