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

class UnitData : public ObjectData {
public:
    UnitData(Dictionary* data);
    virtual ~UnitData();
    float getDefaultAttack() const;
    CC_SYNTHESIZE_READONLY(float, attack, Attack);
    float getInterval() const;
    const char* getFamily() const;
    const char* getMagic() const;
    void updateAttack(const FieldObject* fo);
    virtual void dump() const;
    virtual void updateStatus(const BaseObject* bo);
protected:
    static const char* ATTACK_KEY;
    static const char* INTERVAL_KEY;
    static const char* MAGIC_KEY;
    static const char* FAMILY_KEY;
    static const char* ATTACK_GROUTH_KEY;
};

#endif /* defined(__BabylonClicker__UnitData__) */
