//
//  MainScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#import "MainScene.h"
#import "OpeningLayer.h"
#include "NendModule.h"

MainScene::MainScene()
{
}

MainScene::~MainScene()
{
}

SEL_MenuHandler MainScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler MainScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", MainScene::tappedPreviousButton);
    return NULL;
}

bool MainScene::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    srand((unsigned) time(NULL));
    
    createPhysWorld();
    createGround();
    
    initTouchEventListener();
    
    scheduleUpdate();
    
    char apiKey[] = "a6eca9dd074372c898dd1df549301f277c53f2b9";
    char spotID[] = "3172";
    NendModule::createNADViewBottom(apiKey, spotID);
    
    return true;
}

void MainScene::initTouchEventListener() {
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MainScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(MainScene::onTouchCancelled, this);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
}

bool MainScene::onTouchBegan(Touch *touch, Event *event) {
    return true;
}

void MainScene::onTouchEnded(Touch *touch, Event *event) {
    Box2dSpriteData data = createRandomBox2DSpriteData();
    this->drawBox2dSpriteAt(data, touch->getLocation());
};

void MainScene::onTouchMoved(Touch *touch, Event *event) {
}

void MainScene::onTouchCancelled(Touch *touch, Event *event) {
}

void MainScene::update(float delta){
    int velocityIterations = 8;
    int positionIteretions = 1;
    world->Step(delta, velocityIterations, positionIteretions);
    
    // 物体静止時に演算を省略する
    world->SetAllowSleeping(true);
    
    // 貫通しないように連続計算
    world->SetContinuousPhysics(true);
}

void MainScene::createPhysWorld() {
    b2Vec2 gravity;
    gravity.Set(0,-10);
    world = new b2World(gravity);
}

void MainScene::drawBox2dSpriteAt(MainScene::Box2dSpriteData data, Point pos) {
    if (data.file == NULL) {
        return;
    }
    
    b2Body* body;
    b2BodyDef bodyDef;
    b2CircleShape shape;
    b2FixtureDef fixtureDef;
    
    PhysicsSprite* physicsSprite = PhysicsSprite::create(data.file);
    float scale = Director::getInstance()->getContentScaleFactor();
    physicsSprite->cocos2d::Node::setScale(scale);
    
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set((pos.x) / PT_RATIO, (pos.y) / PT_RATIO);
    bodyDef.userData = physicsSprite;
    
    body = world->CreateBody(&bodyDef);
    
    shape.m_radius = physicsSprite->getContentSize().width / PT_RATIO;
    fixtureDef.shape = &shape;
    fixtureDef.density = data.density;
    fixtureDef.friction = data.friction;
    fixtureDef.restitution = 0.6;
    
    body->CreateFixture(&fixtureDef);
    
    this->addChild(physicsSprite);
    physicsSprite->setB2Body(body);
    physicsSprite->setPTMRatio(PT_RATIO);
    physicsSprite->setPosition(pos);
}

MainScene::Box2dSpriteData MainScene::createRandomBox2DSpriteData() {
    SpriteType type;
    float rnd = CCRANDOM_0_1();
    if (rnd < 0.02) {
        type = SpriteType::Heart;
    } else if (rnd < 0.33) {
        type = SpriteType::Star;
    } else if (rnd < 0.66) {
        type = SpriteType::Circle;
    } else {
        type = SpriteType::Box;
    }
    return createBox2DSpriteData(type);
}

void MainScene::createGround() {
    Size winSize = Director::getInstance()->getWinSize();
    b2BodyDef groundBodyDef;
    groundBodyDef.position.SetZero();
    
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PT_RATIO,0));
    groundBody->CreateFixture(&groundBox,0);
    
    // top
    groundBox.Set(b2Vec2(0,winSize.height/PT_RATIO), b2Vec2(winSize.width/PT_RATIO,winSize.height/PT_RATIO));
    groundBody->CreateFixture(&groundBox,0);
    
    // left
    //groundBox.Set(b2Vec2(0,winSize.height/PT_RATIO), b2Vec2(0,0));
    //groundBody->CreateFixture(&groundBox,0);
    
    // right
    //groundBox.Set(b2Vec2(winSize.width/PT_RATIO,winSize.height/PT_RATIO), b2Vec2(winSize.width/PT_RATIO,0));
    //groundBody->CreateFixture(&groundBox,0);
}

MainScene::Box2dSpriteData MainScene::createBox2DSpriteData(SpriteType type) {
    Box2dSpriteData sprite;
    if (type == SpriteType::Circle) {
        sprite.file = "circle.png";
        sprite.density = 10.0;
        sprite.friction = 0.3;
    } else if (type == SpriteType::Box) {
        sprite.file = "box.png";
        sprite.density = 50.0;
        sprite.friction = 10.0;
    } else if (type == SpriteType::Star) {
        sprite.file = "star.png";
        sprite.density = 0.05;
        sprite.friction = 0.01;
    } else if (type == SpriteType::Heart) {
        sprite.file = "heart.png";
        sprite.density = 10000.0;
        sprite.friction = 0.01;
    } else {
        sprite.file = NULL;
        sprite.density = 0;
        sprite.friction = 0;
    }
    return sprite;
}

void MainScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedPreviousButton eventType = %d", pControlEventType);
    NodeLoaderLibrary* nodeLoaderLibrary = NodeLoaderLibrary::getInstance();
    nodeLoaderLibrary->registerNodeLoader("OpeningLayer", OpeningLayerLoader::loader());
    CCBReader* ccbReader = new CCBReader(nodeLoaderLibrary);
    Node* node = ccbReader->readNodeGraphFromFile("Opening.ccbi");
    Scene* scene = Scene::create();
    if (node != NULL)
    {
        scene->addChild(node);
    }
    ccbReader->release();
    Director::getInstance()->replaceScene(scene);
}

void MainScene::onExit() {
    EventDispatcher::getInstance()->removeAllListeners();
    Layer::onExit();
}