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
#include "ComponentCreator.h"

USING_NS_CC;
USING_NS_CC_EXT;

class MainScene : public Layer
, public CCBSelectorResolver
{
    
public:
    enum {
        DIALOG_TAG_Summon,
        DIALOG_TAG_Item,
        DIALOG_TAG_Magic,
        DIALOG_TAG_Battle,
        DIALOG_TAG_None
    } DIALOG_TAG;
    MainScene();
    virtual ~MainScene();
    static MainScene* create();
    void initFirst();
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object* pTarget, const char* pSelectorName);
    Node* getBattleViewNode();
    void showBattleView();
private:
    bool _doneInitDraw = false;
    int _currentDialog;
    int _currentObjectID;
    Sprite* _bossSprite;
    ComponentCreator* _componentCreator;
    
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
    void dialogCloseCallback(Object* sender);
    void dialogReturnCallback(Object* sender);
    void scrollViewButtonCallback(Object* sender);
    void detailButtonCallback(Object* sender);
    bool isShowingDialog();
    bool isShowingDetail();
    
    void showDialog(int dialogID);
    void showDetail(int dialogID, int objectID);
    void hideDialog();
    void hideBattleView();
    void initDialog();
};

class MainSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainScene);
};


#endif /* defined(__Casidra__MainScene__) */
