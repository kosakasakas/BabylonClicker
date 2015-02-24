#ifndef __Opening_SCENE_H__
#define __Opening_SCENE_H__

#include "cocos2d.h"

class Opening : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    CREATE_FUNC(Opening);
};

#endif // __Opening_SCENE_H__
