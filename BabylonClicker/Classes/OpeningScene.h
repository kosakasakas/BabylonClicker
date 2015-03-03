#ifndef __Opening_SCENE_H__
#define __Opening_SCENE_H__

#include "LPLayer.h"
#include "Observer.h"

class Opening : public LPLayer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Opening);
    
    virtual void onNotice(Ref* sender);
};

#endif // __Opening_SCENE_H__
