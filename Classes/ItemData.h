//
//  ItemData.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/15.
//
//

#ifndef __BabylonClicker__ItemData__
#define __BabylonClicker__ItemData__

#include <iostream>
#include "ObjectData.h"

class ItemData : public ObjectData {
public:
    ItemData(Dictionary* data);
    virtual ~ItemData();
};

#endif /* defined(__BabylonClicker__ItemData__) */
