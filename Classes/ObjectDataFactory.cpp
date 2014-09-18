//
//  ObjectDataFactory.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "ObjectDataFactory.h"

ObjectDataFactory::ObjectDataFactory(const char* filePath)
{
    unicornPlistLoader = new UnicornPlistLoader(filePath);
}

ObjectDataFactory::~ObjectDataFactory()
{
    delete unicornPlistLoader;
}

void ObjectDataFactory::dump() const {
    CCLOG("======ObjectDataFactory::dump()======");
    unicornPlistLoader->dump();
}

void ObjectDataFactory::dumpPropertyValueAtIndex(int index) const {
    CCLOG("======ObjectDataFactory::dumpPropertyValueAtIndex======");
    unicornPlistLoader->dumpPropertyValueAtIndex(index);
}

int ObjectDataFactory::getPropertyNum() const {
    return unicornPlistLoader->getPropertyNum();
}

int ObjectDataFactory::getObjectNum() const {
    return unicornPlistLoader->getObjectNum();
}

Array* ObjectDataFactory::getPropertyArray() const {
    return unicornPlistLoader->getPropertyArray();
}

Dictionary* ObjectDataFactory::getPropertyValueAtIndex(int index) const {
    return unicornPlistLoader->getPropertyValueAtIndex(index);
}

ObjectData* ObjectDataFactory::create(int index){
    ObjectData* obj = createObjectData(index);
    return obj;
}

ObjectData* ObjectDataFactory::createObjectData(int index){
    ObjectData* data = new ObjectData(getPropertyValueAtIndex(index));
    return data;
}

Dictionary* ObjectDataFactory::getDictionary() {
    return unicornPlistLoader->getDictionary();
}
