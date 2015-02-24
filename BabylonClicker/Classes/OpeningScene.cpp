#include "OpeningScene.h"
#include "littlePony.h"

USING_NS_CC;

Scene* Opening::createScene()
{
    auto scene = Scene::create();
    auto layer = Opening::create();
    scene->addChild(layer);

    return scene;
}

// on "init" you need to initialize your instance
bool Opening::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    // load scene by little pony.
    auto al = AssetLoader::getInstatnce();
    auto openingNode = (Node*)al->create("test.plist", "opening");
    this->addChild(openingNode);
    
    return true;
}
