//
//  UnicornScrollableMenu.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/07.
//
//

#ifndef __BabylonClicker__UnicornScrollableMenu__
#define __BabylonClicker__UnicornScrollableMenu__

#include "cocos2d.h"

USING_NS_CC;

class UnicornScrollableMenu : public Menu {
public:
    CREATE_FUNC(UnicornScrollableMenu);
    
    virtual bool onTouchBegan(Touch *touch, Event *event);
    void setValidTouchRectInWorldSpace(Rect rect) { this->validTouchRectInWorldSpace = rect; };
private:
    Rect validTouchRectInWorldSpace;
};


#endif /* defined(__BabylonClicker__UnicornScrollableMenu__) */
