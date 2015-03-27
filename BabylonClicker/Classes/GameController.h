//
//  GameController.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/27.
//
//

#ifndef __BabylonClicker__GameController__
#define __BabylonClicker__GameController__

#include "cocos2d.h"
#include "SceneState.h"

using namespace cocos2d;

class GameController : public Ref
{
public:
    static const int animationInterval;
    
    GameController();
    virtual ~GameController();
    static GameController* getInstatnce();
    virtual bool init();
    CREATE_FUNC(GameController);
    
    void setRootLayer(Layer* scene);
    
    void updateGameLogic(float dt);
    void updateRenderingSystem(float dt);
    
private:
    static GameController* _singleton;
    SceneStateMap* _sceneStateMap;
    Layer* _root;
};

#endif /* defined(__BabylonClicker__GameController__) */
