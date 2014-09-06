//
//  UnicornMenuSprite.cpp
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#include "UnicornMenuSprite.h"

void UnicornMenuSprite::selected()
{
    CCMenuItemSprite::selected();
    //runAction(EaseElasticOut::create(ScaleTo::create(SCALE_ACTION_DURATION, mOldScaleX * SCALE_EFFECT_FACTOR, mOldScaleY* SCALE_EFFECT_FACTOR)));
}

void UnicornMenuSprite::unselected()
{
    CCMenuItemSprite::unselected();
    //runAction(EaseElasticOut::create(ScaleTo::create(SCALE_ACTION_DURATION, mOldScaleX, mOldScaleY)));
}