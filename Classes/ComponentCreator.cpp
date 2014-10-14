//
//  ComponentCreator.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#include "ComponentCreator.h"
#include "UCPlistLoader.h"
#include "BattleController.h"
#include "UnitFactory.h"
#include "ItemFactory.h"
#include "MagicFactory.h"
#include "cocos-ext.h"
#include "UCMenuSprite.h"
#include "UCScrollView.h"
#include "UCScrollableMenu.h"
#include "MainScene.h"
#include "Utility.h"
#include "UnitNode.h"

USING_NS_CC_EXT;

Point ComponentCreator::bossPosition = Point(160, 160);

ComponentCreator::ComponentCreator(Layer* layer)
: bossOrder(-1000)
{
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

Node* ComponentCreator::getScrollComponent(int dialogID, SEL_MenuHandler callback) {
    Array* components = createScrollComponent(dialogID);
    int nodeTag = getNodeTagFromDialogID(dialogID);
    
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
        UCMenuSprite* btnItem = UCMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
        menuItemArray->addObject(btnItem);
        btnItem->addChild(dynamic_cast<Node*>(components->getObjectAtIndex(i)));
        btnItem->setTag(nodeTag + i);
    }
    UCScrollableMenu* btnMenu = (UCScrollableMenu*)UCScrollableMenu::createWithArray(menuItemArray);
    btnMenu->alignItemsVerticallyWithPadding(buttonPosOffset);
    btnMenu->setPosition(Point(0.5*scrollSize.width, 0.5*scrollSize.height));
    container->addChild(btnMenu);
    
    UCScrollView *scrollViewNode = UCScrollView::create(btnMenu);
    scrollViewNode->setClippingToBounds(true);
    scrollViewNode->setContainer(container);
    scrollViewNode->setViewSize(Size(battleViewSize.width, battleViewSize.height - topPosOffset));
    scrollViewNode->setContentOffset(Point(0,-(scrollHeight-2*battleViewSize.height) - battleViewSize.height - topPosOffset));
    scrollViewNode->setDirection(CustomScrollView::Direction::VERTICAL);
    scrollViewNode->setPosition(battlePoint - Point(0.5*battleViewSize.width, 0.5*battleViewSize.height) - (battlePoint - uiNodePoint) - (battlePoint - uiNodePoint));
    scrollViewNode->setTag(NODE_TAG_ScrolleView);
    return scrollViewNode;
}

Node* ComponentCreator::getDetailComponent(int dialogID, int objectID, SEL_MenuHandler callback) {
    Node* output = new Node();
    output->setContentSize(getBattleNode()->getContentSize());
    output->setPosition(0.f, 95.f);
    
    ObjectData* od = getObjectData(dialogID, objectID);
    CCASSERT(od != NULL, "can not get Object Data.");
    
    // update damage frame.
    LabelTTF* damageLabel = getTopDamageLabel();
    if (damageLabel != NULL) {
        damageLabel->setString(od->getName());
    }
    
    std::string spritePath = od->getSpriteFilePath();
    auto objectSprite = Sprite::create(spritePath.c_str());
    if (objectSprite == NULL) {
        return output;
    }
    objectSprite->setPosition(Point(120.f, 175.f));
    output->addChild(objectSprite);
    
    Scale9Sprite* buttonSprite = Scale9Sprite::create("button_black.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
    Size buttonSize = Size(180.f, 35.f);
    buttonSprite->setContentSize(buttonSize);
    UCMenuSprite* btnItem = UCMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
    LabelTTF* buttonLabel = LabelTTF::create("召喚", defaultFont.c_str(), 12);
    buttonLabel->setPosition(Point(0.5*buttonSize.width, 0.5*buttonSize.height));
    btnItem->addChild(buttonLabel);
    Menu* btnMenu = Menu::create(btnItem, NULL);
    btnMenu->setPosition(Point(160.f, 35.f));
    btnMenu->setTag(NODE_TAG_DetailFireButton + objectID);
    output->addChild(btnMenu);
    
    return output;
}


Node* ComponentCreator::createMainButtonMenu(cocos2d::SEL_MenuHandler callback) {
    int buttonNum = 4;
    Size winSize = Director::getInstance()->getWinSize();
    Array* menuItemArray = Array::create();
    for (int i = 0; i < buttonNum; ++i) {
        Scale9Sprite* buttonSprite = Scale9Sprite::create("button_black.png", Rect(0,0,81.5, 51.5), Rect(20,10,41.5,31.5));
        buttonSprite->setContentSize(*mainButtonSize);
        UCMenuSprite* btnItem = UCMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
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

Node* ComponentCreator::getDialogButton(int type, SEL_MenuHandler callback) {
    Sprite* buttonSprite;
    if (type == 0) {
        buttonSprite = Sprite::create("dialog_button.png");
    } else {
        buttonSprite = Sprite::create("dialog_button_return.png");
    }
    UCMenuSprite* btnItem = UCMenuSprite::create(buttonSprite, buttonSprite, parentLayer, callback);
    Menu* btnMenu = Menu::createWithItem(btnItem);
    btnMenu->setPosition(Point(298.f, 381.f));
    return btnMenu;
}

Array* ComponentCreator::createScrollComponent(int dialogID)
{
    Array* result = Array::create();
    UCPlistLoader* upLoader = new UCPlistLoader("revelReleaseList.plist");
    Dictionary* dic = upLoader->getDictionary();
    
    const char* typeName = getDialogTypeString(dialogID).c_str();
    
    Array* list = (Array*)(dic->objectForKey(typeName));
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


int ComponentCreator::getNodeTagFromDialogID(int dialogID) {
    if (dialogID == MainScene::DIALOG_TAG_Summon) {
        return NODE_TAG_ScrollSummonButtons;
    } else if (dialogID == MainScene::DIALOG_TAG_Magic) {
        return NODE_TAG_ScrollMagicButtons;
    } else if (dialogID == MainScene::DIALOG_TAG_Item) {
        return NODE_TAG_ScrollItemButtons;
    } else if (dialogID == MainScene::DIALOG_TAG_Battle) {
        return NODE_TAG_ScrollBattleButtons;
    } else {
        return -1;
    }
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

void ComponentCreator::cleanBattleNode() {
    cleanNode(NODE_TAG_BattleNode);
}

void ComponentCreator::cleanDamageFrame() {
    auto targetNode = parentLayer->getChildByTag(NODE_TAG_TopNode)->getChildByTag(NODE_TAG_TopDamage);
    if (targetNode == NULL) {
        return;
    }
    targetNode->removeAllChildren();
}

bool ComponentCreator::isCorrectSender(Object* sender, int tag) {
    Node* node = dynamic_cast<Node*>(sender);
    int senderTag = node->getTag();
    return (tag == senderTag) ? true : false;
}

int ComponentCreator::getIdfromScrollViewButtonSender(Object* sender) {
    Node* node = dynamic_cast<Node*>(sender);
    int senderTag = node->getTag();
    // 値の大きいものから評価する
    if (senderTag / NODE_TAG_ScrollBattleButtons > 0) {
        return senderTag - NODE_TAG_ScrollSummonButtons;
    } else if (senderTag / NODE_TAG_ScrollMagicButtons > 0) {
        return senderTag - NODE_TAG_ScrollMagicButtons;
    } else if (senderTag / NODE_TAG_ScrollItemButtons > 0) {
        return senderTag - NODE_TAG_ScrollItemButtons;
    } else if (senderTag / NODE_TAG_ScrollSummonButtons > 0) {
        return senderTag - NODE_TAG_ScrollSummonButtons;
    }
    return -1;
}

std::string ComponentCreator::getDialogTypeString(int dialogID) {
    std::string name;
    if (dialogID == MainScene::DIALOG_TAG_Summon) {
        name = "summon";
    } else if (dialogID == MainScene::DIALOG_TAG_Item) {
        name = "item";
    } else if (dialogID == MainScene::DIALOG_TAG_Magic) {
        name = "magic";
    } else if (dialogID == MainScene::DIALOG_TAG_Battle) {
        name = "battle";
    }
    return name;
}

ObjectData* ComponentCreator::getObjectData(int dialogID, int objectID) {
    GameObject* gameObject = getGameObject(dialogID, objectID);
    if (gameObject == NULL) {
        return NULL;
    }
    return gameObject->getObjectData();
}

GameObject* ComponentCreator::getGameObject(int dialogID, int objectID) {
    GameObjectFactory* objectFactory;
    if (dialogID == MainScene::DIALOG_TAG_Summon) {
        objectFactory = new UnitFactory();
    } else if (dialogID == MainScene::DIALOG_TAG_Item) {
        objectFactory = new ItemFactory();
    } else if (dialogID == MainScene::DIALOG_TAG_Magic) {
        objectFactory = new MagicFactory();
    } else if (dialogID == MainScene::DIALOG_TAG_Battle) {
    }
    GameObject* gameObject = objectFactory->create(objectID);
    CC_SAFE_RELEASE(objectFactory);
    return gameObject;
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

LabelTTF* ComponentCreator::getTopDamageLabel() {
    return (LabelTTF*)getTopNode()->getChildByTag(NODE_TAG_TopDamage)->getChildByTag(NODE_TAG_TopDamageLabel);
}

void ComponentCreator::updateUnitSprite() {
    updateUnitPosition();
    updateUnitOrder();
}

void ComponentCreator::updateUnitPosition() {
    Array* unitArray = BattleController::getInstance()->getActiveUnitCage()->getUnitArray();
    Dictionary* dic = Dictionary::createWithContentsOfFile("battleFieldData.plist");
    Array* array = (Array*)dic->objectForKey("field");
    int summonedNum = BattleController::getInstance()->getActiveUnitCage()->getUnitArray()->count();
    int num = 0;
    for (int i = 0; i < array->count(); ++i) {
        Dictionary* posDic = dynamic_cast<Dictionary*>(array->getObjectAtIndex(i));
        int columnNum = UCPlistLoader::getInt(posDic, "num");
        float height = UCPlistLoader::getFloat(posDic, "height");
        float scale = UCPlistLoader::getFloat(posDic, "scale");
        float interval = UCPlistLoader::getFloat(posDic, "interval");
        for (int j = 0; j < columnNum; ++j) {
            if (num >= summonedNum) {
                CC_SAFE_DELETE(dic);
                return;
            }
            Unit* unit = dynamic_cast<Unit*>(unitArray->getObjectAtIndex(summonedNum - 1 - num));
            UnitNode* uNode = (UnitNode*)unit->getUnitNode();
            uNode->setScale(scale);
            float winWidth = Director::getInstance()->getWinSize().width;
            Point pos = Point(0.5*winWidth - pow(-1,(j%2))*((j+1)/2)*interval, height);
            uNode->setDefaultPoint(pos);
            ++num;
        }
    }
}

void ComponentCreator::updateUnitOrder() {
    UnitCage* uCage = BattleController::getInstance()->getActiveUnitCage();
    Array* uArray = uCage->getUnitArray();
    int order = 0;
    Size size = getBattleNode()->getContentSize();
    float heightThreshold = 0.5*size.height;
    float unitHeight;
    Object* it;
    CCARRAY_FOREACH_REVERSE(uArray, it) {
        Unit* u = dynamic_cast<Unit*>(it);
        Node* uNode = u->getUnitNode();
        unitHeight = uNode->getPosition().y;
        if (unitHeight < heightThreshold) {
            uNode->setZOrder(order);
        } else {
            uNode->setZOrder(order + bossOrder - 1);
        }
        --order;
    }
}

void ComponentCreator::initDamageFrame(int sceneTag) {
    cleanDamageFrame();
    if (sceneTag == SCENE_TAG_DETAIL) {
        LabelTTF* damageLabel = LabelTTF::create();
        damageLabel->setFontSize(12.f);
        damageLabel->setFontName(defaultFont.c_str());
        damageLabel->setString("initialized.");
        damageLabel->setColor(whiteColor);
        damageLabel->setTag(NODE_TAG_TopDamageLabel);
        auto damage = getTopNode()->getChildByTag(NODE_TAG_TopDamage);
        Size damageFrameSize = damage->getContentSize();
        damageLabel->setPosition(Point(0.5*damageFrameSize.width, 0.5*damageFrameSize.height));
        damage->addChild(damageLabel);
    } else if(sceneTag == SCENE_TAG_SELECT) {
    } else if (sceneTag == SCENE_TAG_BATTLE) {
        LabelTTF* damageLabel = LabelTTF::create();
        damageLabel->setFontSize(10.f);
        damageLabel->setFontName(defaultFont.c_str());
        damageLabel->setString("Player Data");
        damageLabel->setColor(whiteColor);
        damageLabel->setPosition(Point(95, 36));
        damageLabel->setTag(NODE_TAG_TopDamageLabel);
        auto damage = getTopNode()->getChildByTag(NODE_TAG_TopDamage);
    
        User* user = (User*) BattleController::getInstance()->getField()->getUser();
        Sprite* soulIcon = Sprite::create("icon_soul.png");
        soulIcon->setPosition(Point(19, 22));
        LabelTTF* soulLabel = LabelTTF::create();
        soulLabel->setAnchorPoint(Point(0,0.5));
        soulLabel->setFontSize(10.f);
        soulLabel->setColor(whiteColor);
        soulLabel->setString(Utility::getStrFromFloatValue(user->getSoul()));
        soulLabel->setPosition(Point(41,22));
        soulLabel->setTag(NODE_TAG_TopDamageSoulLabel);
    
        UnitCage* cage = (UnitCage*) BattleController::getInstance()->getActiveUnitCage();
        Sprite* unitIcon = Sprite::create("icon_star.png");
        unitIcon->setPosition(Point(123, 22));
        LabelTTF* unitLabel = LabelTTF::create();
        unitLabel->setAnchorPoint(Point(0,0.5));
        unitLabel->setFontSize(10.f);
        unitLabel->setColor(whiteColor);
        unitLabel->setString(Utility::getStrFromFloatInt(cage->getUnitArray()->count()));
        unitLabel->setPosition(Point(144, 22));
        unitLabel->setTag(NODE_TAG_TopDamageUnitLanel);
    
        damage->addChild(damageLabel);
        damage->addChild(soulIcon);
        damage->addChild(soulLabel);
        damage->addChild(unitIcon);
        damage->addChild(unitLabel);
    }
}

void ComponentCreator::updateBossSprite() {
    auto boss = BattleController::getInstance()->getTargetBoss();
    auto bossNode = boss->getUnitNode();
    BossData* bData = (BossData*) boss->getObjectData();
    bossNode->setZOrder(bossOrder);
    bossNode->setDefaultPoint(bossPosition);
    
    auto topNode = getTopNode();
    LabelTTF* name = (LabelTTF*) topNode->getChildByTag(NODE_TAG_NameLabel);
    LabelTTF* lebel = (LabelTTF*) topNode->getChildByTag(NODE_TAG_LebelLabel);
    LabelTTF* hp = (LabelTTF*) topNode->getChildByTag(NODE_TAG_HPLabel);
    name->setString(bData->getName());
    lebel->setString(Utility::getStrFromFloatInt(bData->getLevel()));
    hp->setString(Utility::getStrFromFloatValue(bData->getHP()));
    
    auto hpBar = topNode->getChildByTag(NODE_TAG_HPBar);
    float scale = (float)bData->getHP()/(float)bData->getMaxHP();
    scale = std::min(1.f,std::max(scale, 0.01f));
    hpBar->setScaleX(scale);
    
    auto magicFrame = topNode->getChildByTag(NODE_TAG_MagicFrame);
    Size frameSize = magicFrame->getContentSize();
    auto magicSprite = createMagicIconSprite(bData->getMagic());
    magicSprite->setPosition(Point(0.5*frameSize.width+1, 0.5*frameSize.height));
    magicFrame->removeAllChildren();
    magicFrame->addChild(magicSprite);
}

void ComponentCreator::initBattleView() {
    initDamageFrame(SCENE_TAG_BATTLE);
}

void ComponentCreator::initDetailView() {
    initDamageFrame(SCENE_TAG_DETAIL);
}

void ComponentCreator::initSelectView(int dialogID) {
    initDamageFrame(SCENE_TAG_SELECT);
    std::string dialogName = getDialogTypeString(dialogID);
    std::string path = "title_";
    path.append(dialogName);
    path.append(".png");
    Sprite* title = Sprite::create(path.c_str());
    auto frame = getTopNode()->getChildByTag(NODE_TAG_TopDamage);
    Size frameSize = frame->getContentSize();
    title->setPosition(Point(0.5*frameSize.width, 0.5*frameSize.height + 2));
    frame->addChild(title);
}
