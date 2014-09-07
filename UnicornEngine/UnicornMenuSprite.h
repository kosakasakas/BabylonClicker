//
//  UnicornMenuSprite.h
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#ifndef __BabylonClicker__UnicornMenuSprite__
#define __BabylonClicker__UnicornMenuSprite__

#include <iostream>
#include "custommenusprite.h"

class UnicornMenuSprite : public CustomMenuSprite
{
public:
    UnicornMenuSprite();
    virtual ~UnicornMenuSprite(){};
    
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite = NULL);
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Object* target, SEL_MenuHandler selector);
    static UnicornMenuSprite * create(Node* normalSprite, Node* selectedSprite, Node* disabledSprite, Object* target, SEL_MenuHandler selector);
};

#endif /* defined(__BabylonClicker__UnicornMenuSprite__) */
