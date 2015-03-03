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
    if ( !LPLayer::init() )
    {
        return false;
    }
    
    // plistからシーンを読み込む
    auto littlePony = LittlePonyController::getInstatnce();
    auto opening = (Node*)littlePony->getData("sceneNode.plist", "opening");
    this->addChild(opening);
    
    // UIのコールバック通知を受け取るために自身を登録
    LittlePonyController::getInstatnce()->addToUINotificationCenter(this);
    
    return true;
}

void Opening::willExit() {
    // UIコールバックから自身を外す。onExitだと遅い。
    LittlePonyController::getInstatnce()->removeFromUINotificationCenter(this);
}

void Opening::onNotice(Ref* sender) {
    if (((Node*)sender)->getTag() == START_MAIN_BUTTON_TAG) {
        // シーンの切り替え。LittlePonyのreplaceSceneを使う
        LittlePonyController::getInstatnce()->replaceScene(Main::createScene());
    }
}