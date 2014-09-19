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
    static Node* createBattleViewComponent();
    static Node* createUIViewComponent();
    static Node* createBackNodeComponent();
    static Node* createTopNodeComponent();
    static Node* createIbaraSprite();
    static Node* createWingSprite();
    static Node* createScrollViewNode();
    static Array* createScrollComponent();
    static Array* createButtonComponent();
    static Size* getComponentSize();
private:
    enum {
        NODE_TAG_BackNode = 100,
        NODE_TAG_BattleNode = 200,
        NODE_TAG_UINode = 300,
        NODE_TAG_TopNode = 400,
        
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
    static Node* createComponent(UnitData* ud);
    static Sprite* createMagicIconSprite(const char* magic);
    void initScrollView(cocos2d::SEL_MenuHandler);
    void cleanNode(Node* targetNode);
    Layer* parentLayer;
};

#endif /* defined(__BabylonClicker__ComponentCreator__) */
