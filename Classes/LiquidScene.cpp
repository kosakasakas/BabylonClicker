//
//  LiquidScene.cpp
//  Casidra
//
//  Created by Takahiro Kosaka on 2014/01/04.
//
//

#import "LiquidScene.h"
#import "OpeningLayer.h"

LiquidScene::LiquidScene()
: world(NULL)
, debugDraw(NULL)
, particleSystem(NULL)
, currentLiquidParam(Water)
{
}

LiquidScene::~LiquidScene()
{
    delete world;
    world = NULL;
    
    delete debugDraw;
    debugDraw = NULL;
    
}

SEL_MenuHandler LiquidScene::onResolveCCBCCMenuItemSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOGERROR("name_menu_item = %s", pSelectorName);
    
    return NULL;
}

Control::Handler LiquidScene::onResolveCCBCCControlSelector(cocos2d::Object *pTarget, const char *pSelectorName)
{
    CCLOG("name_control = %s", pSelectorName);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedPreviousButton", LiquidScene::tappedPreviousButton);
    return NULL;
}

bool LiquidScene::init() {
    if ( !Layer::init() ) {
        return false;
    }
    
    srand((unsigned) time(NULL));
    
    createPhysWorld();
    createGround();
    createParticle();
    
    // デバック表示用
    initDebugDraw();
    initTouchEventListener();
    
    Size window = Director::getInstance()->getWinSize();
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 + 33, 33));
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 - 33, 33));
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 + 33 + 66, 33));
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 - 33 - 66, 33));
    
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 + 33 + 66, 33 + 66));
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 - 33 - 66, 33 + 66));
    
    
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 + 33 + 66, 33 + 66 + 66));
    drawBox2dSpriteAt(createBox2DSpriteData(SpriteType::Box), Point(window.width/2.0 - 33 - 66, 33 + 66 + 66));
    
    
    scheduleUpdate();
    
    return true;
}

void LiquidScene::initTouchEventListener() {
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(LiquidScene::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(LiquidScene::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(LiquidScene::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(LiquidScene::onTouchCancelled, this);
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 100);
}

bool LiquidScene::onTouchBegan(Touch *touch, Event *event) {
    scheduleOnce(schedule_selector(LiquidScene::longPressedScheduler), 1.0);
    particleColor.Set(arc4random()%255, arc4random()%255, arc4random()%255, 255);
    return true;
}

void LiquidScene::onTouchEnded(Touch *touch, Event *event) {
    unschedule(schedule_selector(LiquidScene::longPressedScheduler));
    Box2dSpriteData data = createRandomBox2DSpriteData();
    drawParticleGroupAt(data, touch->getLocation());
};

void LiquidScene::onTouchMoved(Touch *touch, Event *event) {
}

void LiquidScene::onTouchCancelled(Touch *touch, Event *event) {
}

void LiquidScene::update(float delta){
    int velocityIterations = 8;
    int positionIteretions = 1;
    world->Step(delta, velocityIterations, positionIteretions);
    
    // 物体静止時に演算を省略する
    world->SetAllowSleeping(true);
    
    // 貫通しないように連続計算
    world->SetContinuousPhysics(true);
    
    // 表示されなくなったパーティクルは消去
    DestroyUndergroundParticle();
}

void LiquidScene::tappedPreviousButton(Object* pSender, Control::EventType pControlEventType)
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

void LiquidScene::longPressedScheduler(float delta) {
    switchLiquidParam();
}

void LiquidScene::createPhysWorld() {
    b2Vec2 gravity;
    gravity.Set(0,-10);
    world = new b2World(gravity);
    
    GLESDebugDraw* debugDraw = new GLESDebugDraw(PT_RATIO);
    world->SetDebugDraw(debugDraw);
}

void LiquidScene::initDebugDraw() {
    if (world != NULL) {
        debugDraw = new GLESDebugDraw(PT_RATIO);
        world->SetDebugDraw(debugDraw);
        uint32 flags = 0;
        flags += b2Draw::e_shapeBit;
        //        flags += b2Draw::e_jointBit;
                flags += b2Draw::e_aabbBit;
        //        flags += b2Draw::e_pairBit;
        //        flags += b2Draw::e_centerOfMassBit;
        flags |= b2Draw::e_particleBit;
        debugDraw->SetFlags(flags);
        debugDraw->SetSolidParticlesEnable(true);
    }
}

void LiquidScene::draw() {
    Layer::draw();
    glEnableVertexAttribArray(0);
    kmGLPushMatrix();
    world->DrawDebugData();
    kmGLPopMatrix();
}

void LiquidScene::drawBox2dSpriteAt(LiquidScene::Box2dSpriteData data, Point pos) {
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
    
    body->CreateFixture(&fixtureDef);
    
    this->addChild(physicsSprite);
    physicsSprite->setB2Body(body);
    physicsSprite->setPTMRatio(PT_RATIO);
    physicsSprite->setPosition(pos);
}

LiquidScene::Box2dSpriteData LiquidScene::createRandomBox2DSpriteData() {
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

void LiquidScene::createGround() {
    if (world != NULL) {
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
}

LiquidScene::Box2dSpriteData LiquidScene::createBox2DSpriteData(SpriteType type) {
    Box2dSpriteData sprite;
    if (type == SpriteType::Circle) {
        sprite.file = "circle.png";
        sprite.density = 10.0;
        sprite.friction = 0.3;
    } else if (type == SpriteType::Box) {
        sprite.file = "box.png";
        sprite.density = 50000.0;
        sprite.friction = 1000.0;
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

void LiquidScene::createParticle() {
    if (world != NULL) {
        particleColor = b2ParticleColor(arc4random()%255, arc4random()%255, arc4random()%255, 255);
        b2ParticleSystemDef psd;
        psd.radius = 4.0/PT_RATIO;
        particleSystem = world->CreateParticleSystem(&psd);
    }
}

void LiquidScene::drawParticleAt(Point pos) {
    if (particleSystem == NULL) {
        return;
    }
    b2ParticleDef pd;
    pd.flags = b2_elasticParticle | b2_colorMixingParticle;
    pd.color.Set(particleColor.r, particleColor.g, particleColor.b, particleColor.a);
    pd.position.Set(pos.x/PT_RATIO, pos.y/PT_RATIO);
    particleSystem->CreateParticle(pd);
}

void LiquidScene::drawParticleGroupAt(Box2dSpriteData spriteData, Point pos) {
    if (spriteData.file == NULL || particleSystem == NULL) {
        return;
    }
    
    b2CircleShape ballShape;
    ballShape.m_radius = 40.0/PT_RATIO;
    
    b2ParticleGroupDef groupDef;
    groupDef.shape = &ballShape;
    groupDef.flags = (currentLiquidParam == LiquidScene::Elastic) ? b2_elasticParticle : b2_waterParticle;
    groupDef.color.Set(particleColor.r, particleColor.g, particleColor.b, particleColor.a);
    groupDef.position.Set(pos.x/PT_RATIO, pos.y/PT_RATIO);
    particleSystem->CreateParticleGroup(groupDef);
}

void LiquidScene::DestroyUndergroundParticle() {
    b2Vec2* v = particleSystem->GetPositionBuffer();
    for(int i = 0; i < particleSystem->GetParticleCount(); ++i, ++v) {
        const bool is_remove = v->y < 0;
        if (is_remove) {
            particleSystem->DestroyParticle(i);
        }
    }
}

void LiquidScene::switchLiquidParam() {
    std::string nextParam = "";
    if (currentLiquidParam == LiquidScene::Water) {
        nextParam = "弾性体";
        currentLiquidParam = LiquidScene::Elastic;
    } else if (currentLiquidParam == LiquidScene::Elastic) {
        nextParam = "水";
        currentLiquidParam = LiquidScene::Water;
    }
    std::string str = "パラメータを" + nextParam + "に変更します。";
    MessageBox(str.c_str(), "OK");
}

void LiquidScene::onExit() {
    EventDispatcher::getInstance()->removeAllListeners();
    Layer::onExit();
}