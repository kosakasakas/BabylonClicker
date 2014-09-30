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

float ObjectData::getDefaultCost() const {
    return getFloatValue(COST_KEY);
}

int ObjectData::getObjectID() const {
    return getIntValue(OBJECTID_KEY);
}

const char* ObjectData::getGrade() const {
    return getCharValue("grade");
}

const char* ObjectData::getName() const {
    return getCharValue(NAME_KEY);
}

const char* ObjectData::getDescription() const {
    return getCharValue(DESCRIPTION_KEY);
}

std::string ObjectData::getSpriteFileString() {
    int i = getObjectID();
    char buf[5];
    sprintf(buf, "%d", i);
    
    std::string path;
    path.append(getObjectType());
    path.append("_");
    path.append(buf);
    
    return path;
}

std::string ObjectData::getSpriteFilePath() {
    std::string file = getSpriteFileString();
    file.append(".png");
    return file;
}

std::string ObjectData::getMiniSpriteFilePath() {
    std::string file = getSpriteFileString();
    file.append("_mini_");
    file.append(".png");
    return file;
}

void ObjectData::updateStatus(const BaseObject* data){
    update();
}

void ObjectData::incrementLevel() {
    ++level;
    update();
}

void ObjectData::setLevel(int inputLevel) {
    level = inputLevel;
    update();
}

void ObjectData::reduceLevel(int value) {
    level -= value;
    level = (level<0) ? 0 : level;
    update();
}

void ObjectData::updateCost() {
    float defCost = getDefaultCost();
    float cGrouth = getFloatValue(COST_GROWTH_KEY);
    for(int i = 0; i < level; i++) {
        defCost *= cGrouth;
    }
    cost = defCost;
}

void ObjectData::update() {
    updateCost();
}

void ObjectData::dump() const{
    CCLOG("======ObjectData Class======");
    CCLOG("level: %d", getLevel());
    CCLOG("cost: %f", getCost());
    CCLOG("objectID: %d", getObjectID());
    CCLOG("name: %s", getName());
    CCLOG("description: %s", getDescription());
}