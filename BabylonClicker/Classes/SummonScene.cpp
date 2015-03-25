#include "SummonScene.h"
#include "littlePony.h"
#include "MainScene.h"
#include "LPScrollableLayer.h"

USING_NS_CC;

// nodeのタグ一覧。桁数が増える＝下の階層を意味する
#define ROOT_NODE_TAG 3

#define SUB_VIEW_TAG 30

#define BACK_BUTTON_TAG 300
#define RETURN_BUTTON_TAG 301
#define SCROLL_VIEW_TAG 302

#define SCROLL_BUTTON_TAG 3000

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
    
    setScrollableContainer();
    
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
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SUB_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(true);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(false);
}

void Summon::showReturnButton() {
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SUB_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(false);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(true);
}

void Summon::setScrollableContainer() {
    
    int buttonNum = 10;
    
    // ValueMapにパラメータを入れる
    ValueMap body;
    ValueVector vec;
    ValueMap containerValueMap;
    body.emplace("type", Value("button"));
    body.emplace("def", Value("scrollableButtonDef"));
    body.emplace("anchor_x", Value(0.5));
    body.emplace("anchor_y", Value(0.5));
    body.emplace("pos_x", Value(160));
    body.emplace("pos_y", Value(0));
    body.emplace("size_width", Value(210));
    body.emplace("size_height", Value(60));
    body.emplace("tag", Value(SCROLL_BUTTON_TAG));
    body.emplace("useRelative", Value(true));
    body.emplace("use_list", Value(true));
    body.emplace("list_column_num", Value(buttonNum));
    body.emplace("list_h_padding", Value(20));
    vec.emplace_back(Value(body));
    containerValueMap.emplace("container", Value(vec));
    
    // パラメータからcontainerNodeを作成する
    NodeFactory* nf = NodeFactory::create();
    Node* container = nf->getContainerNode(containerValueMap);
    Size containerSize = container->getContentSize();
    
    // scrollViewに対してcontainerNodeをsetする
    LPScrollableLayer* slayer = (LPScrollableLayer*)this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SUB_VIEW_TAG)->getChildByTag(SCROLL_VIEW_TAG);
    Size viewSize = slayer->getViewSize();
    slayer->setContentSize(containerSize);
    slayer->setContentOffset(Vec2(0, (viewSize.height - containerSize.height)), false);
    slayer->setLPContainer((Menu*)container);
    
}