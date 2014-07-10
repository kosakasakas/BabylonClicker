//
//  OpeningLayer.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__OpeningLayer__
#define __Casidra__OpeningLayer__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
USING_NS_CC_EXT;

class OpeningLayer : public Layer
, public CCBSelectorResolver
{
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object * pTarget, const char* pSelectorName);
    void tappedStartMainSceneButton(Object* pSender, Control::EventType pControlEventType);
    void tappedStartLiquidPhysButton(Object* pSender, Control::EventType pControlEventType);
    void tappedStartSampleGameButton(Object* pSender, Control::EventType pControlEventType);
    
    void startMainScene();
    void startLiquidPhysScene();
    void startSampleGameScene();
    
public:
    OpeningLayer();
    virtual ~OpeningLayer();
    virtual void onEnter();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(OpeningLayer, create);
};

class OpeningLayerLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(OpeningLayerLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(OpeningLayer);
};

#endif /* defined(__Casidra__OpeningLayer__) */
