//
//  UnicornMenuSprite.h
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#ifndef __BabylonClicker__UnicornMenuSprite__
#define __BabylonClicker__UnicornMenuSprite__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class UnicornMenuSprite : public MenuItemSprite
{
public:
    UnicornMenuSprite();
    virtual ~UnicornMenuSprite(){};
    
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = NULL);
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector);
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector);
    
    /// Play a sound effect when the item is activated
    void setSoundEffect(const char *filename) { mSoundEffect = filename; }
    
    /// Override CCNode methods
    virtual void onEnter();
    virtual void onExit();
    
    /// Override CCMenuItem methods
    virtual void selected();    /// Get focus
    virtual void unselected();  /// Lost focus
    virtual void activate();
    
    virtual void postponedActivate(float dt);
    
protected:
    float mOldScaleX, mOldScaleY;
    std::string mSoundEffect;
};

#endif /* defined(__BabylonClicker__UnicornMenuSprite__) */
