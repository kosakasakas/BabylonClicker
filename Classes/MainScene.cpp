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
#include "BattleController.h"
#include "UnitField.h"
#include "ComponentCreator.h"

MainScene::MainScene()
: _bossSprite(NULL)
, _currentDialog(DIALOG_TAG_None)
, _currentObjectID(-1)
{
    /*
    Array* unitArray = BattleController::getInstance()->getActiveUnitCage()->getUnitArray();
    Object* it;
    CCARRAY_FOREACH(unitArray, it)
    {
        Unit* u = dynamic_cast<Unit*>(it);
        this->addChild(u->getUnitNode());
    }
     */
    
    // critical node
    this->addChild(BattleController::getInstance()->getCritical());
    _componentCreator = new ComponentCreator(this);
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
    
    GameConfig* config = BattleController::getInstance()->getConfig();
    char* apiKey = (char*)config->getNendApiKey();
    char* spotID = (char*)config->getNendSpotID();
    //NendModule::createNADViewBottom(apiKey, spotID);
    
    return true;
}

void MainScene::initFirst() {
    auto btnMenu = _componentCreator->createMainButtonMenu(menu_selector(MainScene::buttonCallback));
    auto topNode = _componentCreator->getTopNode();
    topNode->addChild(btnMenu);
    
    // summon boss.
    auto boss = BattleController::getInstance()->getTargetBoss();
    boss->summon(_componentCreator->getBattleNode());
    
    showBattleView();
}

MainScene* MainScene::create() {
    MainScene* ptr = new MainScene();
    if (ptr != NULL && ptr->init())
    {
        ptr->autorelease();
        return ptr;
    }
    CC_SAFE_DELETE(ptr);
    return NULL;
}

void MainScene::initDialog() {
}

void MainScene::showDialog(int dialogID) {
    if(!isShowingDialog() || isShowingDetail()) {
        auto scrollViewNode = _componentCreator->getScrollComponent(dialogID, menu_selector(MainScene::scrollViewButtonCallback));
        auto uiNode = _componentCreator->getUiNode();
        auto leftHashiraSprite = _componentCreator->getLeftHashiraSprite();
        auto rightHashiraSprite = _componentCreator->getRightHashiraSprite();
        auto cancelButtonMenu = _componentCreator->getDialogButton(0, menu_selector(MainScene::dialogCloseCallback));
        uiNode->addChild(leftHashiraSprite);
        uiNode->addChild(rightHashiraSprite);
        uiNode->addChild(scrollViewNode);
        uiNode->addChild(cancelButtonMenu);
        hideBattleView();
    }
    _currentObjectID = -1;
}

void MainScene::showDetail(int dialogID, int objectID) {
    if(!isShowingDetail()) {
        auto detailComponent = _componentCreator->getDetailComponent(dialogID, objectID, menu_selector(MainScene::detailButtonCallback));
        auto uiNode = _componentCreator->getUiNode();
        auto leftHashiraSprite = _componentCreator->getLeftHashiraSprite();
        auto rightHashiraSprite = _componentCreator->getRightHashiraSprite();
        auto returnButtonMenu = _componentCreator->getDialogButton(1, menu_selector(MainScene::dialogReturnCallback));
        uiNode->addChild(leftHashiraSprite);
        uiNode->addChild(rightHashiraSprite);
        uiNode->addChild(returnButtonMenu);
        uiNode->addChild(detailComponent);
    }
}

void MainScene::showBattleView() {
    auto battleView = _componentCreator->getBattleNode();
    battleView->setVisible(true);
    
    // setting for uiNode
    auto uiNode = _componentCreator->getUiNode();
    _componentCreator->cleanUiNode();
    auto* ibaraSprite = _componentCreator->getIbaraSprite();
    auto wingSprite = _componentCreator->getWingSprite();
    uiNode->addChild(ibaraSprite);
    uiNode->addChild(wingSprite);
    
    // setting for Unit Sprites.
    _componentCreator->updateUnitSprite();
    
    // setting for Boss Sprite.
    _componentCreator->updateBossSprite();
}

void MainScene::hideDialog() {
    _componentCreator->cleanUiNode();
}

void MainScene::hideBattleView() {
    auto battleView = _componentCreator->getBattleNode();
    battleView->setVisible(false);
}

void MainScene::buttonCallback(Object* sender) {
    CCLOG("call setting button");
    if (_componentCreator->isSummonButton(sender)) {
        CCLOG("tappedSummonButton");
        if (!isShowingDialog()) {
            showDialog(DIALOG_TAG_Summon);
            _currentDialog = DIALOG_TAG_Summon;
        } else if (_currentDialog == DIALOG_TAG_Summon) {
            hideDialog();
            showBattleView();
            _currentDialog = DIALOG_TAG_None;
        }
    }
}

void MainScene::dialogCloseCallback(Object* sender) {
    CCLOG("MainScene::dialogCloseCallback");
    hideDialog();
    showBattleView();
    _currentDialog = DIALOG_TAG_None;
}

void MainScene::dialogReturnCallback(Object* sender) {
    CCLOG("MainScene::dialogReturnCallback");
    hideDialog();
    showDialog(_currentDialog);
}

void MainScene::scrollViewButtonCallback(Object* sender) {
    CCLOG("MainScene::scrollViewButtonCallback called.");
    int id = _componentCreator->getIdfromScrollViewButtonSender(sender);
    if (id != -1) {
        CCLOG("catch view button id: %d", id);
        if (_currentDialog == DIALOG_TAG_Summon) {
            hideDialog();
            showDetail(DIALOG_TAG_Summon, id);
            _currentObjectID = id;
        }
    }
}

void MainScene::detailButtonCallback(Object* sender) {
    CCLOG("MainScene::detailButtonCallback called.");
    GameObject* obj = _componentCreator->getGameObject(_currentDialog, _currentObjectID);
    obj->summon(_componentCreator->getBattleNode());
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
    
    auto battleStage = _componentCreator->getBattleNode();
    if (battleStage->getBoundingBox().containsPoint(touch->getLocation())) {
        auto boss = BattleController::getInstance()->getTargetBoss();
        if (boss) {
            boss->damage(100.f); // todo get val from user data.
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
    showBattleView();
}

void MainScene::addBossNode() {
    if (_bossSprite == NULL) {
        _bossSprite = Sprite::create("summon_4.png");
        auto battleStage = _componentCreator->getBattleNode();
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

bool MainScene::isShowingDialog() {
    if (_currentDialog != DIALOG_TAG_None) {
        return true;
    }
    return false;
}

bool MainScene::isShowingDetail() {
    if (_currentObjectID != -1) {
        return true;
    }
    return false;
}

void MainScene::tappedSummonButton(Object* pSender, Control::EventType pControlEventType)
{
    CCLOG("tappedSummonButton eventType = %d", pControlEventType);
    if (_currentDialog == DIALOG_TAG_Summon) {
        hideDialog();
        _currentDialog = DIALOG_TAG_None;
    } else {
        showDialog(DIALOG_TAG_Summon);
    }
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

Node* MainScene::getBattleViewNode() {
    return _componentCreator->getBattleNode();
}