//
//  UnicornPlistLoader.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#include "UnicornPlistLoader.h"

UnicornPlistLoader::UnicornPlistLoader(const char* filePath)
{
    dictionary = Dictionary::createWithContentsOfFile(filePath);
}

UnicornPlistLoader::~UnicornPlistLoader()
{
    dictionary->release();
}

void UnicornPlistLoader::dump() const {
    CCLOG("======UnicornPlistLoader::dump()======");
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

void UnicornPlistLoader::dumpPropertyValueAtIndex(int index) const {
    CCLOG("UnicornPlistLoader::dumpPropertyValueAtIndex: %d", index);
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

int UnicornPlistLoader::getPropertyNum() const {
    Array* array = getPropertyArray();
    if (array != NULL) {
        return array->count();
    } else {
        return 0;
    }
}

int UnicornPlistLoader::getObjectNum() const {
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

Array* UnicornPlistLoader::getPropertyArray() const {
    if (dictionary != NULL) {
        return dictionary->allKeys();
    } else {
        return NULL;
    }
}

Dictionary* UnicornPlistLoader::getPropertyValueAtIndex(int index) const {
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