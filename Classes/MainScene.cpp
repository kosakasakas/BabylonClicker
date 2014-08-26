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
#import "UCAnimation.h"
#include "GameController.h"
#include "BattleController.h"
#include "UnitField.h"

MainScene::MainScene()
: _bossSprite(NULL)
{
    Array* unitArray = BattleController::getInstance()->getActiveUnitCage()->getUnitArray();
    Object* it;
    CCARRAY_FOREACH(unitArray, it)
    {
        Unit* u = dynamic_cast<Unit*>(it);
        this->addChild(u->getUnitNode());
    }
    
    // critical node
    this->addChild(BattleController::getInstance()->getCritical());
    
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
    CCLOG("====MainScene::init()====");
    
    srand((unsigned) time(NULL));
    
    initTouchEventListener();
    
    scheduleUpdate();
    
    GameConfig* config = GameController::getInstance()->getConfig();
    char* apiKey = (char*)config->getNendApiKey();
    char* spotID = (char*)config->getNendSpotID();
    //NendModule::createNADViewBottom(apiKey, spotID);
    
    return true;
}

void MainScene::setting() {
    //
    auto node = this->getChildByTag(NODE_TAG_UINode)->getChildByTag(NODE_TAG_ScrolleView);
    auto node2 = node->getChildByTag(NODE_TAG_ScrolleLayer);
    int a = 0;
    int b = a;
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
    if (!_doneInitDraw) {
        return true;
    }
    
    auto battleStage = this->getChildByTag(NODE_TAG_UINode)->getChildByTag(NODE_TAG_BattleStageNode);
    if (battleStage->getBoundingBox().containsPoint(touch->getLocation())) {
        if(_bossSprite != NULL && _bossSprite->getNumberOfRunningActions() == 0) {
            _bossSprite->runAction(UCAnimation::getDamageAction(_bossSprite->getPosition()));
            
            // family level up
            //FieldObject* fo = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUnitFamilyField()->getObjectAtIndex(Field::UFFT_Maririka));
            FieldObject* fo = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUnitMagicField()->getObjectAtIndex(Field::MFT_Dark));
            fo->incrementLevel();
            fo->dump();
        }
    }
    return true;
}

void MainScene::onTouchEnded(Touch *touch, Event *event) {
    CCLOG("====onTouchEnded====");
}

void MainScene::onTouchMoved(Touch *touch, Event *event) {
}

void MainScene::onTouchCancelled(Touch *touch, Event *event) {
}

void MainScene::update(float delta){
    if (!_doneInitDraw) {
        initDraw();
        _doneInitDraw = true;
    }
    draw(delta);
}

void MainScene::initDraw() {
    addBossNode();
    addUnitNode();
}

void MainScene::addBossNode() {
    if (_bossSprite == NULL) {
        _bossSprite = Sprite::create("star.png");
        auto battleStage = this->getChildByTag(NODE_TAG_UINode)->getChildByTag(NODE_TAG_BattleStageNode);
        Size size = battleStage->getContentSize();
        _bossSprite->setPosition(Point(size.width/2.0, size.height/2.0));
        battleStage->addChild(_bossSprite);
    }
}

void MainScene::addUnitNode() {
    
}

void MainScene::draw(float delta) {
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