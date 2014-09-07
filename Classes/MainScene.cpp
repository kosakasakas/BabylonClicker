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
#include "UnicornScrollView.h"
#include "UnicornMenuSprite.h"

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
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedSummonButton", MainScene::tappedSummonButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedItemButton", MainScene::tappedItemButton);
    CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "tappedMagicButton", MainScene::tappedMagicButton);
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

void MainScene::showSelectDialog() {
    //UnicornScrollView *scrollViewNode = (UnicornScrollView*)(this->getChildByTag(NODE_TAG_UINode)->getChildByTag(NODE_TAG_ScrolleView));
    
    auto battleStageNode = this->getChildByTag(NODE_TAG_UINode)->getChildByTag(NODE_TAG_BattleStageNode);
    Size battleViewSize = battleStageNode->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    
    int buttonNum = 10;
    float topPosOffset = 80;
    float bottomPosOffset = 10;
    float buttonPosOffset = 20;
    Size buttonSize = Size(160, 40);
    //float scrollHeight = topPosOffset + buttonNum*(buttonSize.height+buttonPosOffset) + bottomPosOffset;
    float scrollHeight =  buttonNum*(buttonSize.height);
    Size scrollSize = Size(battleViewSize.width, scrollHeight);
    Node* container = Node::create();
    Point absPoint = battleStageNode->convertToWorldSpace(battleStageNode->getPosition());
    Point battlePoint = battleStageNode->getPosition();
    //absPoint = Point(absPoint.x, absPoint.y + battleViewSize.height);
    container->setContentSize(scrollSize);
    Point containerPoint = Point(battlePoint.x, battlePoint.y+battleViewSize.height - scrollHeight);
    //container->setPosition(containerPoint);
    container->setAnchorPoint(Point(0,0));
    
    /*
    LayerColor* layer = LayerColor::create(Color4B(51, 75, 112, 255), scrollSize.width, scrollSize.height);
    //layer->setAnchorPoint(Point(0.0,1.0));
    layer->setPosition(containerPoint);
    this->getChildByTag(NODE_TAG_UINode)->addChild(layer);
     */
    
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        Scale9Sprite* buttonSprite = Scale9Sprite::create("button.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
        buttonSprite->setContentSize(buttonSize);
    
        //MenuItemSprite* btnItem = MenuItemSprite::create(buttonSprite, buttonSprite, this, menu_selector(MainScene::buttonCallback));
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, this, menu_selector(MainScene::buttonCallback));
        //btnItem->setPosition(Point(0, 0.5*scrollSize.height - 0.5*buttonSize.height - topPosOffset - i*(buttonSize.height + buttonPosOffset)));
        //btnItem->setAnchorPoint(Point(0.0,1.0));
        btnItem->setPosition(Point(0.5*battleViewSize.width, -i*buttonSize.height));
        menuItemArray->addObject(btnItem);
    }
    Menu* btnMenu = Menu::createWithArray(menuItemArray);
    //btnMenu->setAnchorPoint(Point(0.0, 1.0));
    btnMenu->setPosition(containerPoint);
    container->addChild(btnMenu);
    
    UnicornScrollView *scrollViewNode = UnicornScrollView::create(btnMenu);
    scrollViewNode->setTag(NODE_TAG_ScrolleView);
    //scrollViewNode->setPosition(battleStageNode->getPosition());
    scrollViewNode->setClippingToBounds(false);
    scrollViewNode->setContentSize(scrollSize);
    scrollViewNode->setContainer(container);
    scrollViewNode->setViewSize(battleViewSize);
    //scrollViewNode->setPosition(Point(0,0));
    //scrollViewNode->setContentOffset(absPoint);
    scrollViewNode->setDirection(ScrollView::Direction::VERTICAL);
    
    this->getChildByTag(NODE_TAG_UINode)->addChild(scrollViewNode);
}

void MainScene::buttonCallback(Object* sender) {
    CCLOG("call setting button");
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

void MainScene::tappedSummonButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedSummonButton eventType = %d", pControlEventType);
    showSelectDialog();
}

void MainScene::tappedMagicButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedMagicButton eventType = %d", pControlEventType);
}

void MainScene::tappedItemButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedItemButton eventType = %d", pControlEventType);
}

void MainScene::onExit() {
    EventDispatcher::getInstance()->removeAllListeners();
    Layer::onExit();
}