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
    dictionary = Dictionary::createWithContentsOfFile(filePath);
}

ObjectDataFactory::~ObjectDataFactory()
{
    dictionary->release();
}

void ObjectDataFactory::dump() {
    CCLOG("======Game Data======");
    if (dictionary != NULL) {
        CCLOG("property num: %d", getPropertyNum());
        CCLOG("object num: %d", getObjectNum());
        Array* property = getPropertyArray();
        if(property != NULL) {
            Object* it;
            Object* ij;
            CCARRAY_FOREACH(property, it)
            {
                String* key = dynamic_cast<String*>(it);
                CCLOG("===key: %s===", key->getCString());
                Array* objects = (Array*)dictionary->objectForKey(key->getCString());
                int count = 0;
                if (objects != NULL) {
                    CCARRAY_FOREACH(objects, ij)
                    {
                        String* object = dynamic_cast<String*>(ij);
                        CCLOG("value %d: %s", count, object->getCString());
                        ++count;
                    }
                }
            }
        }
    }
    CCLOG("dump ended.");
}

void ObjectDataFactory::dumpPropertyValueAtIndex(int index) {
    CCLOG("======ObjectDataFactory======");
    CCLOG("dumpPropertyValueAtIndex: %d", index);
    if(0 > index || index > getObjectNum()) {
        CCLOG("index over flow..");
        return;
    }
    Dictionary* dict = getPropertyValueAtIndex(index);
    Array* property = getPropertyArray();
    if (dict != NULL && property != NULL) {
        Object* it;
        CCARRAY_FOREACH(property, it)
        {
            String* key = dynamic_cast<String*>(it);
            CCLOG("key: %s, value: %s", key->getCString(), ((String*)dict->objectForKey(key->getCString()))->getCString());
        }
    }
    CCLOG("dump ended.");
}

int ObjectDataFactory::getPropertyNum() {
    Array* array = getPropertyArray();
    if (array != NULL) {
        return array->count();
    } else {
        return 0;
    }
}

int ObjectDataFactory::getObjectNum() {
    if (dictionary != NULL) {
        Array* property = getPropertyArray();
        if(property != NULL) {
            String* key = (String*)property->getObjectAtIndex(0);
            Array* object = (Array*)dictionary->objectForKey(key->getCString());
            if (object != NULL) {
                return object->count();
            }
        }
    }
    return 0;
}

Array* ObjectDataFactory::getPropertyArray() {
    if (dictionary != NULL) {
        return dictionary->allKeys();
    } else {
        return NULL;
    }
}

Dictionary* ObjectDataFactory::getPropertyValueAtIndex(int index) {
    if(0 > index || index > getObjectNum()) {
        return NULL;
    }
    Dictionary* result = NULL;
    if (dictionary != NULL) {
        Array* property = getPropertyArray();
        if (property != NULL) {
            Object* it;
            result = new Dictionary();
            CCARRAY_FOREACH(property, it)
            {
                String* key = dynamic_cast<String*>(it);
                Array* objects = (Array*)dictionary->objectForKey(key->getCString());
                result->setObject(objects->getObjectAtIndex(index), key->getCString());
            }
        }
    }
    return result;
}

ObjectData* ObjectDataFactory::create(int index){
    ObjectData* obj = createObjectData(index);
    return obj;
}
