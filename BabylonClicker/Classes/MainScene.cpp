#include "MainScene.h"
#include "littlePony.h"
#include "SummonScene.h"

USING_NS_CC;

// nodeのタグ一覧
#define SUMMON_BUTTON_TAG 200
#define TOOL_BUTTON_TAG 201
#define MAGIC_BUTTON_TAG 202
#define BATTLE_BUTTON_TAG 203

Scene* Main::createScene()
{
    auto scene = Scene::create();
    auto layer = Main::create();
    scene->addChild(layer);

    return scene;
}

bool Main::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto littlePony = LittlePonyController::getInstatnce();
    auto Main = (Node*)littlePony->getData("sceneNode.plist", "main");
    this->addChild(Main);
    
    
    return true;
}

void Main::onNotice(Ref* sender) {
    if (((Node*)sender)->getTag() == SUMMON_BUTTON_TAG) {
        Director::getInstance()->replaceScene(Summon::createScene());
    } else if (((Node*)sender)->getTag() == TOOL_BUTTON_TAG) {
        CCLOG("Tool button pressed!!");
    }  else if (((Node*)sender)->getTag() == MAGIC_BUTTON_TAG) {
        CCLOG("Magic button pressed!!");
    } else if (((Node*)sender)->getTag() == BATTLE_BUTTON_TAG) {
        CCLOG("Battle button pressed!!");
    } else {
        CCLOG("unknown button pressed");
    }
}