//
//  ObjectData.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#include "ObjectData.h"
#include "FieldObject.h"
#include "BattleController.h"

const char* ObjectData::COST_KEY = "cost";
const char* ObjectData::OBJECTID_KEY = "objectID";
const char* ObjectData::NAME_KEY = "name";
const char* ObjectData::DESCRIPTION_KEY = "description";
const char* ObjectData::COST_GROWTH_KEY = "costGrowth";

ObjectData::ObjectData(Dictionary* data)
: level(0)
{
    objData = data;
    cost = getDefaultCost();
}

ObjectData::~ObjectData()
{
    objData->release();
}

int ObjectData::getIntValue(const char* key) const{
    if (objData != NULL) {
        String* val = (String*)objData->objectForKey(key);
        return (val != NULL) ? val->intValue() : 0;
    }
    return 0;
}

float ObjectData::getFloatValue(const char* key) const{
    if (objData != NULL) {
        String* val = (String*)objData->objectForKey(key);
        return (val != NULL) ? val->floatValue() : 0.f;
    }
    return 0.f;
}

const char* ObjectData::getCharValue(const char* key) const{
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

int ObjectData::getDefaultCost() const {
    return getIntValue(COST_KEY);
}

int ObjectData::getObjectID() const {
    return getIntValue(OBJECTID_KEY);
}

const char* ObjectData::getName() const {
    return getCharValue(NAME_KEY);
}

const char* ObjectData::getDescription() const {
    return getCharValue(DESCRIPTION_KEY);
}

void ObjectData::updateStatus(const BaseObject* data){
    updateCost();
}

void ObjectData::incrementLevel() {
    ++level;
    updateCost();
}

void ObjectData::reduceLevel(int value) {
    level -= value;
    level = (level<0) ? 0 : level;
    updateCost();
}

void ObjectData::updateCost() {
    float defCost = getDefaultCost();
    float cGrouth = getFloatValue(COST_GROWTH_KEY);
    for(int i = 0; i < level; i++) {
        defCost *= cGrouth;
    }
    cost = defCost;
}


void ObjectData::dump() const{
    CCLOG("======ObjectData Class======");
    CCLOG("cost: %d", getCost());
    CCLOG("objectID: %d", getObjectID());
    CCLOG("name: %s", getName());
    CCLOG("description: %s", getDescription());
}