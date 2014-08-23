//
//  CriticalNode.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#ifndef __BabylonClicker__CriticalNode__
#define __BabylonClicker__CriticalNode__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class CriticalNode : public Node {
public:
    CriticalNode();
    ~CriticalNode();
    CC_SYNTHESIZE_READONLY(float, criticalLot, CriticalLot);
    void onScheduleUpdate(float delta);
    void generateCriticalLot();
};

#endif /* defined(__BabylonClicker__CriticalNode__) */
