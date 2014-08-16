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
#include "Field.h"
#include "User.h"
#include "GameConfig.h"

class GameController
{
private:
    GameController();
    virtual ~GameController();
    static GameController* _singleton;
public:
    static GameController* getInstance();
    CC_SYNTHESIZE_READONLY(GameConfig*, config, Config);
    CC_SYNTHESIZE_READONLY(Field*, field, Field);
    CC_SYNTHESIZE_READONLY(User*, user, User);
};

#endif /* defined(__UnicornEngine__GameController__) */
