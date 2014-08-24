//
//  CriticalSubjectNode.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/22.
//
//

#ifndef __BabylonClicker__CriticalSubjectNode__
#define __BabylonClicker__CriticalSubjectNode__

#include <iostream>
#include "cocos2d.h"
#include "Subject.h"

USING_NS_CC;

class CriticalSubjectNode : public Node {
public:
    CriticalSubjectNode();
    virtual ~CriticalSubjectNode();
    CC_SYNTHESIZE_READONLY(float, criticalLot, CriticalLot);
    void onUpdateCriticalLot(float delta);
    float generateCriticalLot();
    
    void registerObserver(Observer* o);
    void removeObserver(Observer* o);
    void notifyObservers() const;
private:
    Subject* subject;
};

#endif /* defined(__BabylonClicker__CriticalSubjectNode__) */
