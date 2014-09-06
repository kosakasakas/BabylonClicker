//
//  MainScene.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__MainScene__
#define __Casidra__MainScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <array>

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene : public Layer
, public CCBSelectorResolver
{
private:
    enum {
        NODE_TAG_UINode = 100,
        NODE_TAG_StaticNode = 200,
        NODE_TAG_BattleStageNode = 10,
        NODE_TAG_SummonButton = 15,
        NODE_TAG_MagicButton = 16,
        NODE_TAG_ItemButton = 17,
        NODE_TAG_VSModeButton = 18,
        NODE_TAG_NameLabel = 11,
        NODE_TAG_HPLabel = 13,
        NODE_TAG_ScrolleView = 14,
        NODE_TAG_SelectButton = 21,
        NODE_TAG_ScrolleLayer = 20
    } NODE_TAG;
    
    bool _doneInitDraw = false;
    Sprite* _bossSprite;
    
    void update(float delta);
    void draw(float delta);
    void initTouchEventListener();
    
    void tappedPreviousButton(Object* pSender, Control::EventType pControlEventType);
    
    virtual bool init();
    virtual void onExit();
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    void initDraw();
    void addBossNode();
    void addUnitNode();
    
    void buttonCallback(Object* sender);
    
public:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object* pTarget, const char* pSelectorName);
    
    MainScene();
    virtual ~MainScene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    
    void setting();
};

class MainSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};


#endif /* defined(__Casidra__MainScene__) */
