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

GameObject* MagicFactory::createObject()
{
    Magic* magic = new Magic();
    return magic;
}