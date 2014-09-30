//
//  ComponentCreator.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#ifndef __BabylonClicker__ComponentCreator__
#define __BabylonClicker__ComponentCreator__

#include <iostream>
#include "BaseObject.h"
#include "UnitData.h"
#include "GameObject.h"

class ComponentCreator : public BaseObject {
public:
    ComponentCreator(Layer* layer);
    virtual ~ComponentCreator();
    Node* getIbaraSprite();
    Node* getWingSprite();
    Node* createScrollViewNode();
    Node* getUiNode();
    Node* getBattleNode();
    Node* getTopNode();
    Node* getLeftHashiraSprite();
    Node* getRightHashiraSprite();
    Node* createMainButtonSprite();
    Node* createMainButtonMenu(SEL_MenuHandler callback);
    Node* getScrollComponent(int dialogID, SEL_MenuHandler callback);
    Node* getDetailComponent(int dialogID, int objectID, SEL_MenuHandler callback);
    Node* getDialogButton(int type, SEL_MenuHandler callback);
    void cleanUiNode();
    bool isSummonButton(Object* sender);
    bool isMagicButton(Object* sender);
    bool isItemButton(Object* sender);
    bool isVSModeButton(Object* sender);
    int getIdfromScrollViewButtonSender(Object* sender);
    ObjectData* getObjectData(int dialogID, int objectID);
    GameObject* getGameObject(int dialogID, int objectID);
    std::string getDialogTypeString(int dialogID);
private:
    Layer* parentLayer;
    Size* scrollButtonSize;
    Size* mainButtonSize;
    Color3B whiteColor;
    std::string defaultFont;
    enum {
        NODE_TAG_BackNode = 100,
        NODE_TAG_BattleNode = 200,
        NODE_TAG_UINode = 300,
        NODE_TAG_TopNode = 400,
        NODE_TAG_TopDamage = 410,
        NODE_TAG_TopDamageLabel = 411,
        
        NODE_TAG_ScrollSummonButtons = 1000,
        NODE_TAG_ScrollItemButtons = 2000,
        NODE_TAG_ScrollMagicButtons = 3000,
        NODE_TAG_ScrollBattleButtons = 4000,
        NODE_TAG_DetailFireButton = 5000,
        
        NODE_TAG_SummonButton = 11,
        NODE_TAG_MagicButton = 12,
        NODE_TAG_ItemButton = 13,
        NODE_TAG_VSModeButton = 14,
        NODE_TAG_NameLabel = 15,
        NODE_TAG_HPLabel = 16,
        NODE_TAG_ScrolleView = 17,
        NODE_TAG_SelectButton = 18,
        NODE_TAG_ScrolleLayer = 19,
        NODE_TAG_IbaraSprite = 20,
        NODE_TAG_WingSprite = 21,
        NODE_TAG_HashiraLeftSprite = 22,
        NODE_TAG_HashiraRightSprite = 23
    } NODE_TAG;
    enum {
        BUTTON_TAG_Summon,
        BUTTON_TAG_Item,
        BUTTON_TAG_Magic,
        BUTTON_TAG_Battle,
        DIALOG_TAG_None
    } BUTTON_TAG;
    Node* createComponent(UnitData* ud);
    Sprite* createMagicIconSprite(const char* magic);
    std::string createMainButtonString(int id);
    void initScrollView(cocos2d::SEL_MenuHandler);
    bool isCorrectSender(Object* sender, int tag);
    Array* createScrollComponent(int dialogID);
    Array* createButtonComponent();
    Node* createScrollButtonSprite();
    LabelTTF* getTopDamageLabel();
    void cleanNode(int nodeTag);
    int getNodeTagFromDialogID(int dialogID);
};

#endif /* defined(__BabylonClicker__ComponentCreator__) */
