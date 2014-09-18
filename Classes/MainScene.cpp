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
#include "UnicornScrollableMenu.h"
#include "ScrollComponentCreator.h"

MainScene::MainScene()
: _bossSprite(NULL)
, _currentDialog(DIALOG_TAG_None)
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

void MainScene::initFirst() {
    int buttonNum = 4;
    Size buttonSize = Size(80, 50);
    Size winSize = Director::getInstance()->getWinSize();
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        Scale9Sprite* buttonSprite = Scale9Sprite::create("button_black.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
        buttonSprite->setContentSize(buttonSize);
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, this, menu_selector(MainScene::buttonCallback));
        btnItem->setTag(NODE_TAG_SummonButton+i);
        menuItemArray->addObject(btnItem);
    }
    Menu* btnMenu = Menu::createWithArray(menuItemArray);
    btnMenu->alignItemsHorizontallyWithPadding(0.f);
    btnMenu->setPosition(Point(0.5f*winSize.width, 70.f));
    this->getChildByTag(NODE_TAG_TopNode)->addChild(btnMenu);
    
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
    FieldObject* summonField = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUserField()->getObjectAtIndex(Field::UFT_Summon));
    summonField->incrementLevel();
    summonField->incrementLevel();
    
    Array* components = ScrollComponentCreator::make();
    
    auto uiNode = this->getChildByTag(NODE_TAG_UINode);
    auto battleStageNode = this->getChildByTag(NODE_TAG_BattleNode);
    cleanNode(uiNode);
    
    Sprite* ibaraSprite = Sprite::create("hashira_left.png");
    ibaraSprite->setPosition(Point(24.f, 250.f));
    ibaraSprite->setTag(NODE_TAG_HashiraLeftSprite);
    Sprite* wingSprite = Sprite::create("hashira_right.png");
    wingSprite->setPosition(Point(298.f, 250.f));
    wingSprite->setTag(NODE_TAG_HashiraRightSprite);
    
    uiNode->addChild(ibaraSprite);
    uiNode->addChild(wingSprite);
    
    Size battleViewSize = battleStageNode->getContentSize();
    Size winSize = Director::getInstance()->getWinSize();
    int buttonNum = components->count();
    float topPosOffset = 0;
    float bottomPosOffset = 10;
    float buttonPosOffset = 20;
    Size buttonSize = *ScrollComponentCreator::getComponentSize();
    float scrollHeight =  buttonNum*buttonSize.height + buttonPosOffset*(buttonNum -1);
    Size scrollSize = Size(battleViewSize.width, scrollHeight);
    Node* container = Node::create();
    Point battlePoint = battleStageNode->getPosition();
    Point uiNodePoint = uiNode->getPosition();
    container->setContentSize(scrollSize);
    
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        Scale9Sprite* buttonSprite = Scale9Sprite::create("button.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
        buttonSprite->setContentSize(buttonSize);
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, this, menu_selector(MainScene::buttonCallback));
        menuItemArray->addObject(btnItem);
        btnItem->addChild(dynamic_cast<Node*>(components->getObjectAtIndex(i)));
    }
    UnicornScrollableMenu* btnMenu = (UnicornScrollableMenu*)UnicornScrollableMenu::createWithArray(menuItemArray);
    btnMenu->alignItemsVerticallyWithPadding(buttonPosOffset);
    btnMenu->setPosition(Point(0.5*scrollSize.width, 0.5*scrollSize.height));
    container->addChild(btnMenu);
    
    UnicornScrollView *scrollViewNode = UnicornScrollView::create(btnMenu);
    scrollViewNode->setTag(NODE_TAG_ScrolleView);
    scrollViewNode->setClippingToBounds(true);
    scrollViewNode->setContainer(container);
    scrollViewNode->setViewSize(Size(battleViewSize.width, battleViewSize.height - topPosOffset));
    scrollViewNode->setContentOffset(Point(0,-(scrollHeight-2*battleViewSize.height) - battleViewSize.height - topPosOffset));
    scrollViewNode->setDirection(CustomScrollView::Direction::VERTICAL);
    scrollViewNode->setPosition(battlePoint - Point(0.5*battleViewSize.width, 0.5*battleViewSize.height) - (battlePoint - uiNodePoint) - (battlePoint - uiNodePoint));
    scrollViewNode->setTag(NODE_TAG_ScrolleView);
    uiNode->addChild(scrollViewNode);
}

void MainScene::showDialog(int dialogID) {
    if(!isShowingDialog()) {
        initDialog();
    }
    _currentDialog = dialogID;
}

void MainScene::showBattleView() {
    auto uiNode = this->getChildByTag(NODE_TAG_UINode);
    cleanNode(uiNode);
    
    Sprite* ibaraSprite = Sprite::create("ibara.png");
    ibaraSprite->setPosition(Point(268.f, 262.f));
    ibaraSprite->setTag(NODE_TAG_IbaraSprite);
    Sprite* wingSprite = Sprite::create("wing.png");
    wingSprite->setPosition(Point(14.f, 259.f));
    wingSprite->setTag(NODE_TAG_WingSprite);
    
    uiNode->addChild(ibaraSprite);
    uiNode->addChild(wingSprite);
}

void MainScene::hideDialog() {
    Node* uiNode = this->getChildByTag(NODE_TAG_UINode);
    cleanNode(uiNode);
    _currentDialog = DIALOG_TAG_None;
}

void MainScene::cleanNode(Node* targetNode) {
    if (targetNode == NULL) {
        return;
    }
    targetNode->removeAllChildren();
}

void MainScene::buttonCallback(Object* sender) {
    CCLOG("call setting button");
    Node* node = dynamic_cast<Node*>(sender);
    int tag = node->getTag();
    if (tag == NODE_TAG_SummonButton) {
        CCLOG("tappedSummonButton");
        if (_currentDialog == DIALOG_TAG_Summon) {
            hideDialog();
            showBattleView();
        } else {
            showDialog(DIALOG_TAG_Summon);
        }
    }
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
    
    auto battleStage = this->getChildByTag(NODE_TAG_BattleNode);
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
        auto battleStage = this->getChildByTag(NODE_TAG_BattleNode);
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