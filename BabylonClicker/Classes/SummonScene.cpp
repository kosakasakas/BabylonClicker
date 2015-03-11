#include "SummonScene.h"
#include "littlePony.h"
#include "MainScene.h"

USING_NS_CC;

// nodeのタグ一覧
#define ROOT_NODE_TAG 3
#define SCROLL_VIEW_TAG 30
#define BACK_BUTTON_TAG 300
#define RETURN_BUTTON_TAG 301


Scene* Summon::createScene()
{
    auto scene = Scene::create();
    auto layer = Summon::create();
    scene->addChild(layer);

    return scene;
}

bool Summon::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto littlePony = LittlePonyController::getInstatnce();
    auto Summon = (Node*)littlePony->getData("sceneNode.plist", "summon");
    this->addChild(Summon);
    
    showBackButton();
    
    return true;
}

void Summon::onNotice(Ref* sender) {
    if (((Node*)sender)->getTag() == BACK_BUTTON_TAG) {
        Director::getInstance()->replaceScene(Main::createScene());
    } else if (((Node*)sender)->getTag() == RETURN_BUTTON_TAG) {
        CCLOG("Tool button pressed!!");
    } else {
        CCLOG("unknown button pressed");
    }
}

void Summon::showBackButton() {
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SCROLL_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(true);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(false);
}

void Summon::showReturnButton() {
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SCROLL_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(false);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(true);
}