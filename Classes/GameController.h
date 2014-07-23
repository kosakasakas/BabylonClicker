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

class GameController
{
private:
    
private:
    GameController();
    ~GameController();
    static GameController* _singleton;
public:
    static GameController* getInstance();
};

#endif /* defined(__UnicornEngine__GameController__) */
