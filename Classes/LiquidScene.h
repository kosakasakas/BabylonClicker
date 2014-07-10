//
//  LiquidScene.h
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#ifndef __Casidra__LiquidScene__
#define __Casidra__LiquidScene__

#include "cocos2d.h"
#include "cocos-ext.h"
#import "Box2D/Box2D.h"
#include "GLES-Render.h"
#include <array>

USING_NS_CC;
USING_NS_CC_EXT;

class LiquidScene : public Layer
, public CCBSelectorResolver
{
private:
    enum SpriteType {
        Circle,
        Box,
        Star,
        Heart,
        SpriteTypeNum,
    };
    
    enum LiquidParam {
        Water,
        Elastic,
        LiquidParamNum
    };
    
    typedef struct Box2dSpriteData {
        const char* file;
        float density;
        float friction;
    } Box2dSpriteData;
    
    b2World *world;
    GLESDebugDraw *debugDraw;
    b2ParticleSystem *particleSystem;
    b2ParticleColor particleColor;
    LiquidParam currentLiquidParam;
    
    void update(float delta);
    void createPhysWorld();
    void initDebugDraw();
    void createGround();
    void createParticle();
    void initTouchEventListener();
    
    Box2dSpriteData createBox2DSpriteData(SpriteType type);
    Box2dSpriteData createRandomBox2DSpriteData();
    
    void DestroyUndergroundParticle();
    
    void longPressedScheduler(float delta);
    void switchLiquidParam();
    
    virtual bool init();
    virtual void draw();
    virtual void onExit();
    
    void drawBox2dSpriteAt(Box2dSpriteData spriteData, Point pos);
    void drawParticleAt(Point pos);
    void drawParticleGroupAt(Box2dSpriteData spriteData, Point pos);
    
    bool onTouchBegan(Touch *touch, Event *event);
    void onTouchEnded(Touch *touch, Event *event);
    void onTouchMoved(Touch *touch, Event *event);
    void onTouchCancelled(Touch *touch, Event *event);
    
    void tappedPreviousButton(Object* pSender, Control::EventType pControlEventType);
    
public:
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(Object* pTarget, const char* pSelectorName);
    virtual Control::Handler onResolveCCBCCControlSelector(Object* pTarget, const char* pSelectorName);
    
    LiquidScene();
    virtual ~LiquidScene();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(LiquidScene, create);

};

class LiquidSceneLoader : public cocos2d::extension::LayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(LiquidSceneLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(LiquidScene);
};


#endif /* defined(__Casidra__LiquidScene__) */
