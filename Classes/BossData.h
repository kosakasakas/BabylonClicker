//
//  BossData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__BossData__
#define __BabylonClicker__BossData__

#include <iostream>
#include "UnitData.h"

class BossData : public UnitData {
public:
    BossData(Dictionary* data);
    virtual
    ~BossData();
};

#endif /* defined(__BabylonClicker__BossData__) */
