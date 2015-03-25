#ifndef __Summon_SCENE_H__
#define __Summon_SCENE_H__

#include "cocos2d.h"
#include "Observer.h"
#include "LPLayer.h"

class Summon : public LPLayer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(Summon);
    
    virtual void onNotice(Ref* sender);
    
private:
    void showBackButton();
    void showReturnButton();
    
    void setScrollableContainer();
};

#endif // __Summon_SCENE_H__
