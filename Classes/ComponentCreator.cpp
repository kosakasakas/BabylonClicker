//
//  ComponentCreator.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#include "ComponentCreator.h"
#include "UnicornPlistLoader.h"
#include "BattleController.h"
#include "UnitFactory.h"
#include "cocos-ext.h"
#include "UnicornMenuSprite.h"

USING_NS_CC_EXT;

ComponentCreator::ComponentCreator(Layer* layer) {
    parentLayer = layer;
}

ComponentCreator::~ComponentCreator() {
    parentLayer->release();
}

Node* ComponentCreator::createBattleViewComponent() {
    Node* node = new Node();
    return node;
}
Node* ComponentCreator::createUIViewComponent() {
    Node* node = new Node();
    return node;
}
Node* ComponentCreator::createBackNodeComponent() {
    Node* node = new Node();
    return node;
}
Node* ComponentCreator::createTopNodeComponent() {
    Node* node = new Node();
    return node;
}

void ComponentCreator::initScrollView(cocos2d::SEL_MenuHandler) {
    Array* components = ComponentCreator::createScrollComponent();
    
    auto uiNode = parentLayer->getChildByTag(NODE_TAG_UINode);
    auto battleStageNode = parentLayer->getChildByTag(NODE_TAG_BattleNode);
    cleanNode(uiNode);
    
    uiNode->addChild(ComponentCreator::createIbaraSprite());
    uiNode->addChild(ComponentCreator::createWingSprite());
    
    Size battleViewSize = battleStageNode->getContentSize();
    
    Size winSize = Director::getInstance()->getWinSize();
    int buttonNum = components->count();
    float topPosOffset = 0;
    float bottomPosOffset = 10;
    float buttonPosOffset = 20;
    Size buttonSize = *ComponentCreator::getComponentSize();
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
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, parentLayer, menu_selector(MainScene::buttonCallback));
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

Node* ComponentCreator::createIbaraSprite() {
    Node* node = Sprite::create("hashira_left.png");
    node->setPosition(Point(24.f, 250.f));
    node->setTag(NODE_TAG_IbaraSprite);
    return node;
}
Node* ComponentCreator::createWingSprite() {
    Sprite* wingSprite = Sprite::create("hashira_right.png");
    wingSprite->setPosition(Point(298.f, 250.f));
    wingSprite->setTag(NODE_TAG_WingSprite);
    return wingSprite;
}
Node* ComponentCreator::createScrollViewNode() {
    Array* components = createScrollComponent();
    Size battleViewSize = battleStageNode->getContentSize();
    
    Size winSize = Director::getInstance()->getWinSize();
    int buttonNum = components->count();
    float topPosOffset = 0;
    float bottomPosOffset = 10;
    float buttonPosOffset = 20;
    Size buttonSize = *ComponentCreator::getComponentSize();
    float scrollHeight =  buttonNum*buttonSize.height + buttonPosOffset*(buttonNum -1);
    Size scrollSize = Size(battleViewSize.width, scrollHeight);
    Node* container = Node::create();
    //Point battlePoint = battleStageNode->getPosition();
    //Point uiNodePoint = uiNode->getPosition();
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
}


Array* ComponentCreator::createScrollComponent()
{
    Array* result = Array::create();
    UnicornPlistLoader* upLoader = new UnicornPlistLoader("revelReleaseList.plist");
    Dictionary* dic = upLoader->getDictionary();
    Array* list = (Array*)(dic->objectForKey("Summon"));
    FieldObject* summonField = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUserField()->getObjectAtIndex(Field::UFT_Summon));
    for (int i=0,n=summonField->getLevel(); i <= n; ++i) {
        Array* numList = dynamic_cast<Array*>(list->getObjectAtIndex(i));
        Object* it;
        CCARRAY_FOREACH(numList, it)
        {
            String* val = (String*)it;
            UnitFactory* uFactory = new UnitFactory();
            Unit* unit = (Unit*)uFactory->create(val->intValue());
            Node* node = createComponent((UnitData*)unit->getObjectData());
            result->addObject(node);
        }
    }
    return result;
}

Node* ComponentCreator::createComponent(UnitData* ud) {
    Node *node = new Node();
    node->setContentSize(*getComponentSize());
    
    Sprite* frame = Sprite::create("type.png");
    frame->setPosition(Point(40.0, 52.5));
    Sprite* star = Sprite::create("icon_star.png");
    star->setPosition(Point(36.9, 22.3));
    Sprite* soul = Sprite::create("icon_soul.png");
    soul->setPosition(Point(87.7,24.3));
    Sprite* magic = createMagicIconSprite(ud->getMagic());
    magic->setPosition(Point(40.9, 52.8));
    
    Color3B white = Color3B(255,255,255);
    LabelTTF* nameLabel = LabelTTF::create(ud->getName(), "Arial Rounded MT Bold", 12);
    nameLabel->setAnchorPoint(Point(0,0));
    nameLabel->setPosition(Point(61.9, 46.0));
    nameLabel->setColor(white);
    LabelTTF* starLabel = LabelTTF::create(ud->getGrade(), "Arial Rounded MT Bold", 10);
    starLabel->setAnchorPoint(Point(0,0));
    starLabel->setPosition(Point(50.0, 16.2));
    starLabel->setColor(white);
    LabelTTF* soulLabel = LabelTTF::create("1000", "Arial Rounded MT Bold", 12);
    soulLabel->setAnchorPoint(Point(0,0));
    soulLabel->setPosition(Point(99.5, 16.2));
    soulLabel->setColor(white);
    
    node->addChild(frame);
    node->addChild(magic);
    node->addChild(star);
    node->addChild(soul);
    node->addChild(nameLabel);
    node->addChild(starLabel);
    node->addChild(soulLabel);
    
    return node;
}

Size* ComponentCreator::getComponentSize() {
    Size* size = new Size();
    size->setSize(180, 80);
    return size;
}

Sprite* ComponentCreator::createMagicIconSprite(const char* magic) {
    Sprite* sprite;
    Field::MagicFieldType magicType = Field::getMagicFieldType(magic);
    if (magicType == Field::MFT_Dark) {
        sprite = Sprite::create("icon_dark.png");
    } else if (magicType == Field::MFT_Shine) {
        sprite = Sprite::create("icon_light.png");
    } else if (magicType == Field::MFT_Fire) {
        sprite = Sprite::create("icon_fire.png");
    } else if (magicType == Field::MFT_Water) {
        sprite = Sprite::create("icon_water.png");
    } else if (magicType == Field::MFT_Wood) {
        sprite = Sprite::create("icon_leaf.png");
    } else if (magicType == Field::MFT_Wizard) {
        sprite = Sprite::create("icon_light.png");
    }
    return sprite;
}



void ComponentCreator::cleanNode(Node* targetNode) {
    if (targetNode == NULL) {
        return;
    }
    targetNode->removeAllChildren();
}