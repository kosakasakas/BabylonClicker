//
//  RigidScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#import "RigidScene.h"
#import "OpeningLayer.h"

RigidScene::RigidScene()
{
}

RigidScene::~RigidScene()
{
}

SEL_MenuHandler RigidScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler RigidScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", RigidScene::tappedPreviousButton);
    return NULL;
}

bool RigidScene::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    srand((unsigned) time(NULL));
    
    createPhysWorld();
    createGround();
    
    initTouchEventListener();
    
    scheduleUpdate();
    
    return true;
}

void RigidScene::initTouchEventListener() {
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(RigidScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(RigidScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(RigidScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(RigidScene::onTouchCancelled, this);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
}

bool RigidScene::onTouchBegan(Touch *touch, Event *event) {
    return true;
}

void RigidScene::onTouchEnded(Touch *touch, Event *event) {
    Box2dSpriteData data = createRandomBox2DSpriteData();
    this->drawBox2dSpriteAt(data, touch->getLocation());
};

void RigidScene::onTouchMoved(Touch *touch, Event *event) {
}

void RigidScene::onTouchCancelled(Touch *touch, Event *event) {
}

void RigidScene::update(float delta){
    int velocityIterations = 8;
    int positionIteretions = 1;
    world->Step(delta, velocityIterations, positionIteretions);
    
    // 物体静止時に演算を省略する
    world->SetAllowSleeping(true);
    
    // 貫通しないように連続計算
    world->SetContinuousPhysics(true);
}

void RigidScene::createPhysWorld() {
    b2Vec2 gravity;
    gravity.Set(0,-10);
    world = new b2World(gravity);
}

void RigidScene::drawBox2dSpriteAt(RigidScene::Box2dSpriteData data, Point pos) {
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

RigidScene::Box2dSpriteData RigidScene::createRandomBox2DSpriteData() {
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

void RigidScene::createGround() {
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

RigidScene::Box2dSpriteData RigidScene::createBox2DSpriteData(SpriteType type) {
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

void RigidScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
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

void RigidScene::onExit() {
    EventDispatcher::getInstance()->removeAllListeners();
    Layer::onExit();
}