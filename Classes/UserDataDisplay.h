//
//  UserDataDisplay.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#ifndef __BabylonClicker__UserDataDisplay__
#define __BabylonClicker__UserDataDisplay__

#include <iostream>
#include "ObjectDataDisplay.h"

class UserDataDisplay : public ObjectDataDisplay {
public:
    UserDataDisplay();
    ~UserDataDisplay();
    virtual void updateStatus(const BaseObject* data);
    virtual void draw(const BaseObject* data);
};
#endif /* defined(__BabylonClicker__UserDataDisplay__) */
