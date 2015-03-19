#ifndef __Main_SCENE_H__
#define __Main_SCENE_H__

#include "cocos2d.h"
#include "Observer.h"
#include "LPLayer.h"

class Main : public LPLayer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Main);
    
    virtual void onNotice(Ref* sender);
};

#endif // __Main_SCENE_H__
