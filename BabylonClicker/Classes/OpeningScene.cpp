#include "OpeningScene.h"
#include "littlePony.h"

USING_NS_CC;

#define START_GAME_BUTTON_TAG 10

Opening::Opening()
{
}

Opening::~Opening()
{
    // UIコールバックから自身を外す
    LittlePonyController::getInstatnce()->removeFromUINotificationCenter(this);
}

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
    auto opening = (Node*)littlePony->getData("sceneNode.plist", "main");
    this->addChild(opening);
    
    // UIのコールバック通知を受け取るために自身を登録
    LittlePonyController::getInstatnce()->addToUINotificationCenter(this);
    
    return true;
}

void Opening::onNotice(Ref* sender) {
    if (((Node*)sender)->getTag() == START_GAME_BUTTON_TAG) {
         CCLOG("Start Game Button pressed!!");
    }
}