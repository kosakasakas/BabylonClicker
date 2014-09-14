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
        NODE_TAG_BackNode = 100,
        NODE_TAG_BattleNode = 200,
        NODE_TAG_UINode = 300,
        NODE_TAG_TopNode = 400,
        
        NODE_TAG_SummonButton = 11,
        NODE_TAG_MagicButton = 12,
        NODE_TAG_ItemButton = 13,
        NODE_TAG_VSModeButton = 14,
        NODE_TAG_NameLabel = 15,
        NODE_TAG_HPLabel = 16,
        NODE_TAG_ScrolleView = 17,
        NODE_TAG_SelectButton = 18,
        NODE_TAG_ScrolleLayer = 19,
        NODE_TAG_IbaraSprite = 20,
        NODE_TAG_WingSprite = 21,
        NODE_TAG_HashiraLeftSprite = 22,
        NODE_TAG_HashiraRightSprite = 23
    } NODE_TAG;
    
    enum {
        DIALOG_TAG_Summon,
        DIALOG_TAG_Item,
        DIALOG_TAG_Magic,
        DIALOG_TAG_Battle,
        DIALOG_TAG_None
    } DIALOG_TAG;
    
    bool _doneInitDraw = false;
    int _currentDialog;
    Sprite* _bossSprite;
    
    void update(float delta);
    void draw(float delta);
    void initTouchEventListener();
    
    void tappedPreviousButton(Object* pSender, Control::EventType pControlEventType);
    void tappedSummonButton(Object* pSender, Control::EventType pControlEventType);
    void tappedMagicButton(Object* pSender, Control::EventType pControlEventType);
    void tappedItemButton(Object* pSender, Control::EventType pControlEventType);
    
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
    bool isShowingDialog();
    
    void showDialog(int dialogID);
    void hideDialog();
    void initDialog();
    void showBattleView();
    void cleanNode(Node* targetNode);
    
public:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object* pTarget, const char* pSelectorName);
    
    MainScene();
    virtual ~MainScene();
    
    static MainScene* create();
    //CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(MainScene, create);
    
    void initFirst();
};

class MainSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};


#endif /* defined(__Casidra__MainScene__) */
