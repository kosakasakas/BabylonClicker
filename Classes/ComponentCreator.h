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
    Node* getScrollComponent(SEL_MenuHandler callback);
    Node* getDialogButton(SEL_MenuHandler callback);
    void cleanUiNode();
    bool isSummonButton(Object* sender);
    bool isMagicButton(Object* sender);
    bool isItemButton(Object* sender);
    bool isVSModeButton(Object* sender);
    int getIdfromScrollViewButtonSender(Object* sender);
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
        NODE_TAG_ScrollViewButtons = 500,
        
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
    Array* createScrollComponent();
    Array* createButtonComponent();
    Node* createScrollButtonSprite();
    void cleanNode(int nodeTag);
};

#endif /* defined(__BabylonClicker__ComponentCreator__) */
