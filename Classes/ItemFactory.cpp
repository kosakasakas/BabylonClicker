//
//  ItemFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "ItemFactory.h"
#include "Item.h"

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

GameObject* ItemFactory::createObject() {
    Item* item = new Item();
    return item;
}