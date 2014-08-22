//
//  UserDataDisplay.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#include "UserDataDisplay.h"
#include "User.h"

UserDataDisplay::UserDataDisplay()
{
}

UserDataDisplay::~UserDataDisplay()
{
}

void UserDataDisplay::updateStatus(const BaseObject* data) {
    CCLOG("UserDataDisplay updated");
    draw(data);
}

void UserDataDisplay::draw(const BaseObject* data) {
    const User* user = dynamic_cast<const User*>(data);
    CCLOG("User soul: %f", user->getSoul());
}