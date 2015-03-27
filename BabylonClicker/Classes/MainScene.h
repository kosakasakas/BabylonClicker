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

private:
    void hideMainView();
    void showMainView();
    
    void hideScrollView();
    void showScrollView();
    
    void showBackButton();
    void showReturnButton();
    
    void setScrollableContainer();
};

#endif // __Main_SCENE_H__
