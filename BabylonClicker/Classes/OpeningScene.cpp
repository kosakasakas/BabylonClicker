#include "littlePony.h"
#include "OpeningScene.h"
#include "MainScene.h"

USING_NS_CC;

#define START_MAIN_BUTTON_TAG 10

Scene* Opening::createScene()
{
    auto scene = Scene::create();
    auto layer = Opening::create();
    scene->addChild(layer);

    return scene;
}

bool Opening::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // plistからシーンを読み込む
    auto littlePony = LittlePonyController::getInstatnce();
    auto opening = (Node*)littlePony->getData("sceneNode.plist", "opening");
    this->addChild(opening);
    
    return true;
}

void Opening::onNotice(Ref* sender) {
    if (((Node*)sender)->getTag() == START_MAIN_BUTTON_TAG) {
        // シーンの切り替え。
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, Main::createScene()));
    }
}