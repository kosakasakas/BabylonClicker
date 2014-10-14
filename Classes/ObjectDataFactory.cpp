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
    _ucPlistLoader = new UCPlistLoader(filePath);
}

ObjectDataFactory::~ObjectDataFactory()
{
    delete _ucPlistLoader;
}

void ObjectDataFactory::dump() const {
    CCLOG("======ObjectDataFactory::dump()======");
    _ucPlistLoader->dump();
}

void ObjectDataFactory::dumpPropertyValueAtIndex(int index) const {
    CCLOG("======ObjectDataFactory::dumpPropertyValueAtIndex======");
    _ucPlistLoader->dumpPropertyValueAtIndex(index);
}

int ObjectDataFactory::getPropertyNum() const {
    return _ucPlistLoader->getPropertyNum();
}

int ObjectDataFactory::getObjectNum() const {
    return _ucPlistLoader->getObjectNum();
}

Array* ObjectDataFactory::getPropertyArray() const {
    return _ucPlistLoader->getPropertyArray();
}

Dictionary* ObjectDataFactory::getPropertyValueAtIndex(int index) const {
    return _ucPlistLoader->getPropertyValueAtIndex(index);
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
    return _ucPlistLoader->getDictionary();
}
