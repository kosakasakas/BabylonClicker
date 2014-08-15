//
//  MagicFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "MagicFactory.h"
#include "Magic.h"

MagicFactory::MagicFactory()
{
}

MagicFactory::~MagicFactory()
{
}

GameObject* MagicFactory::createObject(int objectID)
{
    Magic* magic = new Magic();
    return magic;
}