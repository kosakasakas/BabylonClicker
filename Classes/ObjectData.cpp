//
//  ObjectData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "ObjectData.h"

const char* ObjectData::COST_KEY = "cost";
const char* ObjectData::LEVEL_KEY = "level";
const char* ObjectData::OBJECTID_KEY = "objectID";
const char* ObjectData::NAME_KEY = "name";
const char* ObjectData::DESCRIPTION_KEY = "description";

ObjectData::ObjectData(Dictionary* data)
{
    objData = data;
}

ObjectData::~ObjectData()
{
    objData->release();
}

int ObjectData::getIntValue(const char* key) {
    if (objData != NULL) {
        String* val = (String*)objData->objectForKey(key);
        return (val != NULL) ? val->intValue() : 0;
    }
    return 0;
}

float ObjectData::getFloatValue(const char* key) {
    if (objData != NULL) {
        String* val = (String*)objData->objectForKey(key);
        return (val != NULL) ? val->floatValue() : 0.f;
    }
    return 0.f;
}

const char* ObjectData::getCharValue(const char* key) {
    if (objData != NULL) {
        String* name = (String*) objData->objectForKey(key);
        return (name != NULL) ? name->getCString() : "";
    }
    return "";
}

void ObjectData::setIntValue(int val, const char* key) {
    if (objData != NULL) {
        String* str = String::createWithFormat("%d", val);
        objData->setObject(str, key);
    }
}

void ObjectData::setFloatValue(float val, const char* key) {
    if (objData != NULL) {
        String* str = String::createWithFormat("%f", val);
        objData->setObject(str, key);
    }
}

void ObjectData::setCharValue(const char* val, const char* key) {
}

int ObjectData::getCost(){
    return getIntValue(COST_KEY);
}

int ObjectData::getObjectID(){
    return getIntValue(OBJECTID_KEY);
}

int ObjectData::getLevel(){
    return getIntValue(LEVEL_KEY);
}

const char* ObjectData::getName() {
    return getCharValue(NAME_KEY);
}

const char* ObjectData::getDescription() {
    return getCharValue(DESCRIPTION_KEY);
}

void ObjectData::setCost(int value) {
    setIntValue(value, COST_KEY);
}

void ObjectData::setLevel(int value) {
    setIntValue(value, LEVEL_KEY);
}

void ObjectData::dump() {
    CCLOG("======ObjectData Class======");
    CCLOG("cost: %d", getCost());
    CCLOG("level: %d", getLevel());
    CCLOG("objectID: %d", getObjectID());
    CCLOG("name: %s", getName());
    CCLOG("description: %s", getDescription());
}