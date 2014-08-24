//
//  UnitData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__UnitData__
#define __BabylonClicker__UnitData__

#include <iostream>
#include "ObjectData.h"
#include "FieldObject.h"
#include <map>

class UnitData : public ObjectData {
public:
    UnitData(Dictionary* data);
    virtual ~UnitData();
    float getDefaultAttack() const;
    CC_SYNTHESIZE_READONLY(float, attack, Attack);
    CC_SYNTHESIZE_READONLY(int, unitNum, UnitNum);
    float getInterval() const;
    const char* getFamily() const;
    const char* getMagic() const;
    int getSacrifice(int slotID) const;
    int getSacrificeNum(int slotID) const;
    float getCriticalLength() const;
    virtual void dump() const;
    virtual void updateStatus(const BaseObject* bo);
    void incrementUnitNum();
    void reduceUnitNum(int num);
    static int SACRIFICE_SLOT_NUM;
protected:
    void addFamilyOffsetToAttack();
    void addMagicOffsetToAttack();
    void updateAttack();
    static const char* ATTACK_KEY;
    static const char* INTERVAL_KEY;
    static const char* MAGIC_KEY;
    static const char* FAMILY_KEY;
    static const char* ATTACK_GROWTH_KEY;
    static const char* SACRIFICE_KEY[];
    static const char* SACRIFICE_NUM_KEY[];
};

#endif /* defined(__BabylonClicker__UnitData__) */
