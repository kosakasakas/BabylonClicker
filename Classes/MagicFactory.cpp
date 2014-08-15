//
//  MagicFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "MagicFactory.h"
#include "Magic.h"
#include "MagicData.h"
#include "MagicDataFactory.h"

MagicFactory::MagicFactory()
{
}

MagicFactory::~MagicFactory()
{
}

GameObject* MagicFactory::createObject(int objectID)
{
    MagicDataFactory* udFactory = new MagicDataFactory("MagicData.plist");
    MagicData* mData = (MagicData*)udFactory->create(objectID);
    Magic* magic = new Magic(mData);
    return magic;
}