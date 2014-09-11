//
//  UnicornGestureLayer.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/10.
//
//

#ifndef __BabylonClicker__UnicornGestureLayer__
#define __BabylonClicker__UnicornGestureLayer__

#include "XTLayer.h"

class UnicornGestureLayer : public XTLayer {
public:
    UnicornGestureLayer();
    ~UnicornGestureLayer();
    virtual void xtTapGesture(CCPoint position) {}
    virtual void xtDoubleTapGesture(CCPoint position) {}
    virtual void xtLongTapGesture(CCPoint position) {}
    virtual void xtSwipeGesture(XTTouchDirection direction, float distance, float speed) {}
};

#endif /* defined(__BabylonClicker__UnicornGestureLayer__) */
