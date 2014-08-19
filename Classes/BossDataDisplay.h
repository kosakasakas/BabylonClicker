//
//  BossDataDisplay.h
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/08/16.
//
//

#ifndef __BabylonClicker__BossDataDisplay__
#define __BabylonClicker__BossDataDisplay__

#include <iostream>
#include "ObjectDataDisplay.h"

class BossDataDisplay : public ObjectDataDisplay {
public:
    BossDataDisplay();
    virtual ~BossDataDisplay();
    virtual void updateStatus(const BaseObject* data);
    virtual void draw(const BaseObject* data);
};

#endif /* defined(__BabylonClicker__BossDataDisplay__) */
