#include "MainScene.h"
#include "littlePony.h"
#include "LPScrollableLayer.h"

USING_NS_CC;

// nodeのタグ一覧。桁数が増える＝下の階層を意味する
#define ROOT_NODE_TAG      2
#define STATIC_VIEW_TAG    20
#define MAIN_VIEW_TAG      21

#define SUMMON_BUTTON_TAG  200
#define TOOL_BUTTON_TAG    201
#define MAGIC_BUTTON_TAG   202
#define BATTLE_BUTTON_TAG  203

#define SCROLL_VIEW_TAG    3
#define BACK_BUTTON_TAG    30
#define RETURN_BUTTON_TAG  31
#define SCROLL_LAYER_TAG   32
#define SCROLL_BUTTON_TAG  300

#define DIAPLAY_NODE_TAG   4
#define DISPLAY_LABEL_TAG  40


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
    auto rootNode = (Node*)littlePony->getData("sceneNode.plist", "main");
    this->addChild(rootNode);
    
    return true;
}

void Main::onNotice(Ref* sender) {
    switch (((Node*)sender)->getTag()) {
        case SUMMON_BUTTON_TAG:
            hideMainView();
            showScrollView();
            break;
            
        case BACK_BUTTON_TAG:
            hideScrollView();
            showMainView();
            break;
            
        default:
            CCLOG("unknown button pressed");
            break;
    }
}

void Main::hideMainView() {
    this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(MAIN_VIEW_TAG)->setVisible(false);
}

void Main::showMainView() {
    this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(MAIN_VIEW_TAG)->setVisible(true);
}

void Main::hideScrollView() {
    this->getChildByTag(ROOT_NODE_TAG)->removeChildByTag(SCROLL_VIEW_TAG);
}

void Main::showScrollView() {
    auto scrollView = (Node*)LittlePonyController::getInstatnce()->getData("sceneNode.plist", "scrollView");
    this->getChildByTag(ROOT_NODE_TAG)->addChild(scrollView);
    
    setScrollableContainer();
    
    showBackButton();
}

void Main::showBackButton() {
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SCROLL_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(true);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(false);
}

void Main::showReturnButton() {
    auto view = this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SCROLL_VIEW_TAG);
    view->getChildByTag(BACK_BUTTON_TAG)->setVisible(false);
    view->getChildByTag(RETURN_BUTTON_TAG)->setVisible(true);
}


void Main::setScrollableContainer() {
    
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
    Menu* container = (Menu*)nf->getContainerNode(containerValueMap);
    Size containerSize = container->getContentSize();
    
    // scrollViewに対してcontainerNodeをsetする
    LPScrollableLayer* slayer = (LPScrollableLayer*)this->getChildByTag(ROOT_NODE_TAG)->getChildByTag(SCROLL_VIEW_TAG)->getChildByTag(SCROLL_LAYER_TAG);
    Size viewSize = slayer->getViewSize();
    slayer->setContentSize(containerSize);
    slayer->setContentOffset(Vec2(0, (viewSize.height - containerSize.height)), false);
    slayer->setLPContainer(container);
    
    // 動的にラベルにテキストを書き込む
    auto lpc = LittlePonyController::getInstatnce();
    for (int i = 0; i < buttonNum; ++i) {
        char text[256];
        sprintf(text, "hoge %d", i);
        
        Node* button = container->getChildByTag(SCROLL_BUTTON_TAG + i);
        Node* display = (Node*)lpc->getData("sceneNode.plist", "scrollButtonDisplay");
        Label* label = (Label*) display->getChildByTag(DISPLAY_LABEL_TAG);
        label->setString(text);
        button->addChild(display);
    }
}