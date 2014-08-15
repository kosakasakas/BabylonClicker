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

class UnitData : public ObjectData {
public:
    UnitData(Dictionary* data);
    ~UnitData();
};

#endif /* defined(__BabylonClicker__UnitData__) */
