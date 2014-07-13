//
//  AppManager.h
//  UnicornEngine
//
//  Created by 小坂 昂大 on 2014/07/12.
//
//

#ifndef __UnicornEngine__AppManager__
#define __UnicornEngine__AppManager__

#include <iostream>
#include "cocos2d.h"
#include "AppMacros.h"

class AppManager
{
private:
    static AppManager* _singleton;
    
    AppManager();
    virtual ~AppManager();
    void init();
    static Resource getRunningDeviceResource();
    void setAssetResolution();
    
public:
    static AppManager* getInstance();
    CC_SYNTHESIZE_READONLY(DeviceType, _runningDeviceType, RunningDeviceType);
    CC_SYNTHESIZE_READONLY(Resource*, _resource, Resource);
};

#endif /* defined(__UnicornEngine__AppManager__) */
