//
//  Field.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#ifndef __BabylonClicker__Field__
#define __BabylonClicker__Field__

#include <iostream>
#include "cocos2d.h"
#include "BaseObject.h"
#include "FieldObject.h"
#include "UnitData.h"

class Field : virtual public BaseObject {
public:
    Field();
    virtual ~Field();
    typedef enum {
        UFT_Attack,
        UFT_Summon,
        UFT_Magic,
        UFT_Enemy,
        UFT_Rebirth,
        UFT_TypeNum
    } UserFieldType;
    typedef enum {
        MFT_Fire,
        MFT_Water,
        MFT_Wood,
        MFT_Shine,
        MFT_Dark,
        MFT_TypeNum
    } MagicFieldType;
    typedef enum {
        UFFT_Babylon,
        UFFT_Hanaaruki,
        UFFT_Maririka,
        UFFT_Papillon,
        UFFT_TypeNum
    } UnitFamilyFieldType;
    CC_SYNTHESIZE_READONLY(Array*, unitField, UnitField);
    CC_SYNTHESIZE_READONLY(Array*, unitFamilyField, UnitFamilyField);
    CC_SYNTHESIZE_READONLY(Array*, unitMagicField, UnitMagicField);
    CC_SYNTHESIZE_READONLY(Array*, userField, UserField);
    CC_SYNTHESIZE_READONLY(Array*, userMagicField, UserMagicField);
    virtual void dump() const;
    void registUnitFamiryFieldObserver(UnitData* uData);
    void registUnitMagicFieldObserver(Observer* o);
    void registUnitFieldObserver(Observer* o);
    void registUserField(Observer* o);
    void registUserMagicField(Observer* o);
private:
    UnitFamilyFieldType getUnitFamilyFieldType(const char* name);
};
#endif /* defined(__BabylonClicker__Field__) */
