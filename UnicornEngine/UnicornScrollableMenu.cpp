//
//  UnicornScrollableMenu.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/07.
//
//

#include "UnicornScrollableMenu.h"

UnicornScrollableMenu::UnicornScrollableMenu(){
    
}

UnicornScrollableMenu::~UnicornScrollableMenu(){
    
}

UnicornScrollableMenu* UnicornScrollableMenu::createWithArray(Array* pArrayOfItems)
{
    UnicornScrollableMenu *pRet = new UnicornScrollableMenu();
    if (pRet && pRet->initWithArray(pArrayOfItems))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    
    return pRet;
}

bool UnicornScrollableMenu::onTouchBegan(Touch *touch, Event *event) {
    if (!validTouchRectInWorldSpace.size.width || !validTouchRectInWorldSpace.size.height) {
        return Menu::onTouchBegan(touch, event);
    }
    
    Point touchLocation = touch->getLocation();
    if (!validTouchRectInWorldSpace.containsPoint(touchLocation)) {
        return false;
    }
    
    return Menu::onTouchBegan(touch, event);
}