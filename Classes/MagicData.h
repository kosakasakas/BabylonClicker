//
//  MagicData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__MagicData__
#define __BabylonClicker__MagicData__

#include <iostream>
#include "ObjectData.h"

class MagicData : public ObjectData {
public:
    MagicData(Dictionary* data);
    virtual ~MagicData();
};

#endif /* defined(__BabylonClicker__MagicData__) */
