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
#include "UnicornScrollView.h"
#include "UnicornScrollableMenu.h"

USING_NS_CC_EXT;

ComponentCreator::ComponentCreator(Layer* layer) {
    parentLayer = layer;
    scrollButtonSize = new Size();
    scrollButtonSize->setSize(180,80);
    mainButtonSize = new Size();
    mainButtonSize->setSize(80, 50);
    whiteColor = Color3B(255,255,255);
    defaultFont = "Arial Rounded MT Bold";
}

ComponentCreator::~ComponentCreator(){
    parentLayer->release();
}

Node* ComponentCreator::getUiNode() {
    return parentLayer->getChildByTag(NODE_TAG_UINode);
}

Node* ComponentCreator::getBattleNode() {
    return parentLayer->getChildByTag(NODE_TAG_BattleNode);
}

Node* ComponentCreator::getTopNode() {
    return parentLayer->getChildByTag(NODE_TAG_TopNode);
}

Node* ComponentCreator::getScrollComponent(SEL_MenuHandler callback) {
    Array* components = createScrollComponent();
    
    auto uiNode = getUiNode();
    auto battleStageNode = getBattleNode();
    cleanUiNode();
    Size battleViewSize = battleStageNode->getContentSize();
    
    Size winSize = Director::getInstance()->getWinSize();
    int buttonNum = components->count();
    float topPosOffset = 90;
    float buttonPosOffset = 20;
    Size buttonSize = *scrollButtonSize;
    float scrollHeight =  buttonNum*buttonSize.height + buttonPosOffset*(buttonNum -1);
    Size scrollSize = Size(battleViewSize.width, scrollHeight);
    Node* container = Node::create();
    Point battlePoint = battleStageNode->getPosition();
    Point uiNodePoint = uiNode->getPosition();
    container->setContentSize(scrollSize);
    
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        auto buttonSprite = ComponentCreator::createScrollButtonSprite();
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
        menuItemArray->addObject(btnItem);
        btnItem->addChild(dynamic_cast<Node*>(components->getObjectAtIndex(i)));
    }
    UnicornScrollableMenu* btnMenu = (UnicornScrollableMenu*)UnicornScrollableMenu::createWithArray(menuItemArray);
    btnMenu->alignItemsVerticallyWithPadding(buttonPosOffset);
    btnMenu->setPosition(Point(0.5*scrollSize.width, 0.5*scrollSize.height));
    container->addChild(btnMenu);
    
    UnicornScrollView *scrollViewNode = UnicornScrollView::create(btnMenu);
    scrollViewNode->setClippingToBounds(true);
    scrollViewNode->setContainer(container);
    scrollViewNode->setViewSize(Size(battleViewSize.width, battleViewSize.height - topPosOffset));
    scrollViewNode->setContentOffset(Point(0,-(scrollHeight-2*battleViewSize.height) - battleViewSize.height - topPosOffset));
    scrollViewNode->setDirection(CustomScrollView::Direction::VERTICAL);
    scrollViewNode->setPosition(battlePoint - Point(0.5*battleViewSize.width, 0.5*battleViewSize.height) - (battlePoint - uiNodePoint) - (battlePoint - uiNodePoint));
    scrollViewNode->setTag(NODE_TAG_ScrolleView);
    return scrollViewNode;
}

Node* ComponentCreator::createMainButtonMenu(cocos2d::SEL_MenuHandler callback) {
    int buttonNum = 4;
    Size winSize = Director::getInstance()->getWinSize();
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        Scale9Sprite* buttonSprite = Scale9Sprite::create("button_black.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
        buttonSprite->setContentSize(*mainButtonSize);
        UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
        btnItem->setTag(NODE_TAG_SummonButton+i);
        
        LabelTTF* nameLabel = LabelTTF::create(createMainButtonString(i).c_str(), defaultFont.c_str(), 12);
        nameLabel->setPosition(Point(40, 25));
        nameLabel->setColor(whiteColor);
        btnItem->addChild(nameLabel);
        
        menuItemArray->addObject(btnItem);
    }
    Menu* btnMenu = Menu::createWithArray(menuItemArray);
    btnMenu->alignItemsHorizontallyWithPadding(0.f);
    btnMenu->setPosition(Point(0.5f*winSize.width, 70.f));
    return btnMenu;
}

Node* ComponentCreator::createScrollButtonSprite() {
    Scale9Sprite* buttonSprite = Scale9Sprite::create("button.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
    buttonSprite->setContentSize(*scrollButtonSize);
    return buttonSprite;
}

Node* ComponentCreator::getIbaraSprite() {
    Sprite* ibaraSprite = Sprite::create("ibara.png");
    ibaraSprite->setPosition(Point(268.f, 262.f));
    ibaraSprite->setTag(NODE_TAG_IbaraSprite);
    return ibaraSprite;
}

Node* ComponentCreator::getWingSprite() {
    Sprite* wingSprite = Sprite::create("wing.png");
    wingSprite->setPosition(Point(14.f, 259.f));
    wingSprite->setTag(NODE_TAG_WingSprite);
    return wingSprite;
}

Node* ComponentCreator::getLeftHashiraSprite() {
    Node* node = Sprite::create("hashira_left.png");
    node->setPosition(Point(24.f, 250.f));
    node->setTag(NODE_TAG_HashiraLeftSprite);
    return node;
}

Node* ComponentCreator::getRightHashiraSprite() {
    Sprite* wingSprite = Sprite::create("hashira_right.png");
    wingSprite->setPosition(Point(298.f, 250.f));
    wingSprite->setTag(NODE_TAG_HashiraRightSprite);
    return wingSprite;
}

Node* ComponentCreator::getDialogButton(SEL_MenuHandler callback) {
    Sprite* buttonSprite = Sprite::create("dialog_button.png");
    UnicornMenuSprite* btnItem = UnicornMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
    Menu* btnMenu = Menu::createWithItem(btnItem);
    btnMenu->setPosition(Point(298.f, 381.f));
    return btnMenu;
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
            CC_SAFE_RELEASE(uFactory);
        }
    }
    CC_SAFE_DELETE(upLoader);
    return result;
}

Node* ComponentCreator::createComponent(UnitData* ud) {
    Node *node = new Node();
    node->setContentSize(*scrollButtonSize);
    
    Sprite* frame = Sprite::create("type.png");
    frame->setPosition(Point(40.0, 52.5));
    Sprite* star = Sprite::create("icon_star.png");
    star->setPosition(Point(36.9, 22.3));
    Sprite* soul = Sprite::create("icon_soul.png");
    soul->setPosition(Point(87.7,24.3));
    Sprite* magic = createMagicIconSprite(ud->getMagic());
    magic->setPosition(Point(40.9, 52.8));
    
    LabelTTF* nameLabel = LabelTTF::create(ud->getName(), defaultFont.c_str(), 12);
    nameLabel->setAnchorPoint(Point(0,0));
    nameLabel->setPosition(Point(61.9, 46.0));
    nameLabel->setColor(whiteColor);
    LabelTTF* starLabel = LabelTTF::create(ud->getGrade(), defaultFont.c_str(), 10);
    starLabel->setAnchorPoint(Point(0,0));
    starLabel->setPosition(Point(50.0, 16.2));
    starLabel->setColor(whiteColor);
    LabelTTF* soulLabel = LabelTTF::create("1000", defaultFont.c_str(), 12);
    soulLabel->setAnchorPoint(Point(0,0));
    soulLabel->setPosition(Point(99.5, 16.2));
    soulLabel->setColor(whiteColor);
    
    node->addChild(frame);
    node->addChild(magic);
    node->addChild(star);
    node->addChild(soul);
    node->addChild(nameLabel);
    node->addChild(starLabel);
    node->addChild(soulLabel);
    
    return node;
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

std::string ComponentCreator::createMainButtonString(int id) {
    std::string str;
    if (id == BUTTON_TAG_Summon) {
        str = "召喚";
    } else if (id == BUTTON_TAG_Item) {
        str = "道具";
    } else if (id == BUTTON_TAG_Magic) {
        str = "魔術";
    } else if (id == BUTTON_TAG_Battle) {
        str = "対戦";
    }
    return str;
}


void ComponentCreator::cleanNode(int nodeTag) {
    auto targetNode = parentLayer->getChildByTag(nodeTag);
    if (targetNode == NULL) {
        return;
    }
    targetNode->removeAllChildren();
}

void ComponentCreator::cleanUiNode() {
    cleanNode(NODE_TAG_UINode);
}

bool ComponentCreator::isCorrectSender(Object* sender, int tag) {
    Node* node = dynamic_cast<Node*>(sender);
    int senderTag = node->getTag();
    return (tag == senderTag) ? true : false;
}

bool ComponentCreator::isSummonButton(Object* sender) {
    return isCorrectSender(sender, NODE_TAG_SummonButton);
}

bool ComponentCreator::isVSModeButton(Object* sender) {
    return isCorrectSender(sender, NODE_TAG_VSModeButton);
}

bool ComponentCreator::isMagicButton(Object* sender) {
    return isCorrectSender(sender, NODE_TAG_MagicButton);
}

bool ComponentCreator::isItemButton(Object* sender) {
    return isCorrectSender(sender, NODE_TAG_ItemButton);
}