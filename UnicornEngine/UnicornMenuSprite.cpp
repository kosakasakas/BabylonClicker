//
//  UnicornMenuSprite.cpp
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#include "UnicornMenuSprite.h"

UnicornMenuSprite::UnicornMenuSprite()
: CustomMenuSprite()
{}

UnicornMenuSprite * UnicornMenuSprite::create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite)
{
    return UnicornMenuSprite::create(normalSprite, selectedSprite, disabledSprite, NULL, NULL);
}

UnicornMenuSprite * UnicornMenuSprite::create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector)
{
    return UnicornMenuSprite::create(normalSprite, selectedSprite, NULL, target, selector);
}

UnicornMenuSprite * UnicornMenuSprite::create(Node *normalSprite, Node *selectedSprite, Node *disabledSprite, Object *target, SEL_MenuHandler selector)
{
    UnicornMenuSprite *pRet = new UnicornMenuSprite();
    pRet->initWithNormalSprite(normalSprite, selectedSprite, disabledSprite, target, selector);
    pRet->autorelease();
    return pRet;
}