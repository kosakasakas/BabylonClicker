//
//  SceneState.h
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/27.
//
//

#ifndef __BabylonClicker__SceneState__
#define __BabylonClicker__SceneState__

#include "littlePony.h"

//
// SceneStateMapの定義
//
class SceneStateMap : public StateMap
{
public:
    SceneStateMap();
    virtual ~SceneStateMap();
    CREATE_FUNC(SceneStateMap);
    
    virtual bool init();
};

//
// SceneStateの定義
//
enum SCENE_STATE_ID {
    MAIN,
    SUMMON,
    NUM
};

class MainSceneState : public State
{
public:
    MainSceneState();
    virtual ~MainSceneState();
    CREATE_FUNC(MainSceneState);
    
    virtual bool init();
    
    virtual void inState();
    virtual void outState();
    virtual void onState();
    virtual void update();
};

class SummonSceneState : public State
{
public:
    SummonSceneState();
    virtual ~SummonSceneState();
    CREATE_FUNC(SummonSceneState);
    
    virtual bool init();
    
    virtual void inState();
    virtual void outState();
    virtual void onState();
    virtual void update();
};

//
// Transitionの定義
//
class ToMainScene : public Transition
{
public:
    ToMainScene();
    virtual ~ToMainScene();
    CREATE_FUNC(ToMainScene);
    
    virtual bool init();
    
    virtual void transit();
    virtual bool canTransit(State* state);
    virtual State* getNextState();
};

class ToSummonScene : public Transition
{
public:
    ToSummonScene();
    virtual ~ToSummonScene();
    CREATE_FUNC(ToSummonScene);
    
    virtual bool init();
    
    virtual void transit();
    virtual bool canTransit(State* state);
    virtual State* getNextState();
};

//
// TransitionConditionの定義
//
class TestCondition : public TransitCondition
{
public:
    TestCondition();
    virtual ~TestCondition();
    CREATE_FUNC(TestCondition);
    
    virtual bool canTransit(State* state, const ValueMap& args);
};

#endif /* defined(__BabylonClicker__SceneState__) */
