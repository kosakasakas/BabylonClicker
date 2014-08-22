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
#include "UserDataDisplay.h"
#include "BossDataFactory.h"

Field::Field()
{
    unitFamilyField = Array::createWithCapacity(FFT_TypeNum);
    unitFamilyField->retain();
    
    unitMagicField = Array::createWithCapacity(MFT_TypeNum);
    unitMagicField->retain();
    
    userField = Array::createWithCapacity(UFT_TypeNum);
    userField->retain();
    
    userMagicField = Array::createWithCapacity(MFT_TypeNum);
    userMagicField->retain();
    
    for (int i = 0; i < UFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        userField->addObject(fo);
    }
    for (int i = 0; i < FFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        unitFamilyField->addObject(fo);
    }
    for (int i = 0; i < MFT_TypeNum; ++i) {
        FieldObject* fo = new FieldObject();
        unitMagicField->addObject(fo);
        FieldObject* fo2 = new FieldObject();
        userMagicField->addObject(fo2);
    }
    
    UnitDataFactory* udFactory = new UnitDataFactory("unitData.plist");
    int unitNum = udFactory->getObjectNum();
    unitRef = new Array*[unitNum];
    sharedUnitDataArray = Array::createWithCapacity(unitNum);
    sharedUnitDataArray->retain();
    for(int i = 0; i < unitNum; i++) {
        // init unitRef
        unitRef[i] = Array::create();
        unitRef[i]->retain();
        // regist sharedUnitData
        UnitData* uData = (UnitData*)udFactory->create(i);
        sharedUnitDataArray->addObject(uData);
        registUnitFamiryFieldObserver(uData);
        registUnitMagicFieldObserver(uData);
    }
    
    user = new User();
    UserDataDisplay* udDisplay = new UserDataDisplay();
    user->registerObserver(udDisplay);
    
    BossDataFactory* bdFactory = new BossDataFactory("bossData.plist");
    bossNum = bdFactory->getObjectNum();
    bossLevelArray = new int[bossNum];
    for(int i=0; i<bossNum; ++i) {
        bossLevelArray[i] = 0;
    }
}

Field::~Field()
{
    sharedUnitDataArray->release();
    unitFamilyField->release();
    unitMagicField->release();
    userField->release();
    userMagicField->release();
    delete[] unitRef;
    user->release();
    delete[] bossLevelArray;
}

void Field::dump() const{
    CCLOG("======Field Class======");
    Object* it;
    CCLOG("~~~sharedUnitDataArray~~~");
    CCARRAY_FOREACH(sharedUnitDataArray, it)
    {
        UnitData* ud = dynamic_cast<UnitData*>(it);
        ud->dump();
    }
    CCLOG("~~~unitFamilyField~~~");
    CCARRAY_FOREACH(unitFamilyField, it)
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
    FamilyFieldType fft = getFamilyFieldType(uData->getFamily());
    FieldObject* fo = dynamic_cast<FieldObject*>(unitFamilyField->getObjectAtIndex(fft));
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

void Field::registUserField(UnitData* uData) {
}

void Field::registUserMagicField(UnitData* uData) {
}

bool Field::isHavingSharedUnitData(int objectID) {
    UnitData* ud = getSharedUnitData(objectID);
    return (ud != NULL) ? true : false;
}

void Field::setSharedUnitData(UnitData* uData) {
    sharedUnitDataArray->setObject(uData, uData->getObjectID());
}

UnitData* Field::getSharedUnitData(int objectID) {
    return dynamic_cast<UnitData*>(sharedUnitDataArray->getObjectAtIndex(objectID));
}

Array* Field::getUnitRefArray(int objectID) {
    Array* sfArray = unitRef[objectID];
    return sfArray;
}

int Field::getBossLevel(int objectID) const {
    return (0<=objectID && objectID<bossNum) ? bossLevelArray[objectID] : 0;
}

void Field::setBossLevel(int objectID, int level) {
    bossLevelArray[objectID] = level;
}

Field::FamilyFieldType Field::getFamilyFieldType(const char* name) {
    const std::string familyString = name;
    if (familyString.compare("バビロン") == 0) {
        return FFT_Babylon;
    } else if (familyString.compare("ハナアルキ") == 0) {
        return FFT_Hanaaruki;
    } else if (familyString.compare("マリリカ") == 0) {
        return FFT_Maririka;
    } else if (familyString.compare("パピヨン") == 0) {
        return FFT_Papillon;
    } else {
        return FFT_TypeNum;
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