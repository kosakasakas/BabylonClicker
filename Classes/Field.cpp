//
//  Field.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "Field.h"
#include "UnitDataFactory.h"
#include "UnitField.h"

Field::Field()
{
    UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
    int unitNum = udFactory->getObjectNum();
    unitField = Array::createWithCapacity(unitNum);
    unitField->retain();
    
    unitFamilyField = Array::createWithCapacity(UFFT_TypeNum);
    unitFamilyField->retain();
    
    unitMagicField = Array::createWithCapacity(MFT_TypeNum);
    unitMagicField->retain();
    
    userField = Array::createWithCapacity(UFT_TypeNum);
    userField->retain();
    
    userMagicField = Array::createWithCapacity(MFT_TypeNum);
    userMagicField->retain();
    
    for (int i = 0; i < unitNum; ++i) {
        UnitField* fo = new UnitField();
        unitField->addObject(fo);
    }
    for (int i = 0; i < UFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        userField->addObject(fo);
    }
    for (int i = 0; i < UFFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        unitFamilyField->addObject(fo);
    }
    for (int i = 0; i < MFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        unitMagicField->addObject(fo);
        FieldObject* fo2 = new FieldObject();
        userMagicField->addObject(fo2);
    }
}

Field::~Field()
{
    unitField->release();
    unitFamilyField->release();
    unitMagicField->release();
    userField->release();
    userMagicField->release();
}

void Field::dump() const{
    CCLOG("======Field Class======");
    Object* it;
    CCLOG("~~~unitFamilyField~~~");
    CCARRAY_FOREACH(unitFamilyField, it)
    {
        FieldObject* fo = dynamic_cast<FieldObject*>(it);
        fo->dump();
    }
    CCLOG("~~~unitField~~~");
    CCARRAY_FOREACH(unitField, it)
    {
        FieldObject* fo = dynamic_cast<FieldObject*>(it);
        fo->dump();
    }
    CCLOG("~~~unitMagicField~~~");
    CCARRAY_FOREACH(unitMagicField, it)
    {
        FieldObject* fo = dynamic_cast<FieldObject*>(it);
        fo->dump();
    }
    CCLOG("~~~userField~~~");
    CCARRAY_FOREACH(userField, it)
    {
        FieldObject* fo = dynamic_cast<FieldObject*>(it);
        fo->dump();
    }
    CCLOG("~~~userMagicField~~~");
    CCARRAY_FOREACH(userMagicField, it)
    {
        FieldObject* fo = dynamic_cast<FieldObject*>(it);
        fo->dump();
    }
}

void Field::registUnitFamiryFieldObserver(UnitData* uData) {
    UnitFamilyFieldType ufft = getUnitFamilyFieldType(uData->getFamily());
    FieldObject* fo = dynamic_cast<FieldObject*>(unitFamilyField->getObjectAtIndex(ufft));
    if (fo->hasObserver(uData)) {
        CCLOG("Observer is already registered.");
    } else {
        fo->registerObserver(uData);
    }
}

void Field::registUnitMagicFieldObserver(UnitData* uData) {
    MagicFieldType mft = getMagicFieldType(uData->getMagic());
    FieldObject* fo = dynamic_cast<FieldObject*>(unitMagicField->getObjectAtIndex(mft));
    if (fo->hasObserver(uData)) {
        CCLOG("Observer is already registered.");
    } else {
        fo->registerObserver(uData);
    }
}

void Field::registUnitFieldObserver(UnitData* uData) {
    int objectID = uData->getObjectID();
    UnitField* uf = dynamic_cast<UnitField*>(unitField->getObjectAtIndex(objectID));
    if (uf->hasObserver(uData)) {
        // UnitData is shared. so we regist uData only once. 
        CCLOG("Observer is already registered.");
    } else {
        uf->registerObserver(uData);
    }
}

void Field::registUserField(UnitData* uData) {
}

void Field::registUserMagicField(UnitData* uData) {
}

Field::UnitFamilyFieldType Field::getUnitFamilyFieldType(const char* name) {
    const std::string familyString = name;
    if (familyString.compare("バビロン") == 0) {
        return UFFT_Babylon;
    } else if (familyString.compare("ハナアルキ") == 0) {
        return UFFT_Hanaaruki;
    } else if (familyString.compare("マリリカ") == 0) {
        return UFFT_Maririka;
    } else if (familyString.compare("パピヨン") == 0) {
        return UFFT_Papillon;
    } else {
        return UFFT_TypeNum;
    }
}

Field::MagicFieldType Field::getMagicFieldType(const char* magic) {
    const std::string magicString = magic;
    if (magicString.compare("闇") == 0) {
        return MFT_Dark;
    } else if (magicString.compare("水") == 0) {
        return MFT_Water;
    } else if (magicString.compare("火") == 0) {
        return MFT_Fire;
    } else if (magicString.compare("木") == 0) {
        return MFT_Wood;
    } else if (magicString.compare("光") == 0) {
        return MFT_Shine;
    } else {
        return MFT_TypeNum;
    }
}