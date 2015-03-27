//
//  SceneState.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/27.
//
//

#include "SceneState.h"

//
// SceneSatateMapの定義
//
SceneStateMap::SceneStateMap()
{}

SceneStateMap::~SceneStateMap()
{}

bool SceneStateMap::init()
{
    // シーンを全て登録する。
    State* main = MainSceneState::create();
    State* summon = SummonSceneState::create();
    
    main->retain();
    summon->retain();
    
    _states.pushBack(main);
    _states.pushBack(summon);
    
    // 開始シーンを登録
    _currentState = main;
    
    return true;
}

//
// SceneStateの定義
//

// MainScene
MainSceneState::MainSceneState()
{
}

MainSceneState::~MainSceneState()
{
}

bool MainSceneState::init() {
    _stateID = SCENE_STATE_ID::MAIN;
    return true;
}

void MainSceneState::inState() {
    CCLOG("in main state...");
}

void MainSceneState::outState() {
    CCLOG("out main state...");
}

void MainSceneState::onState() {
    CCLOG("on main state...");
}

void MainSceneState::update() {
    CCLOG("MainScene updated.");
}

// SummonScene
SummonSceneState::SummonSceneState()
{
}

SummonSceneState::~SummonSceneState()
{
}

bool SummonSceneState::init() {
    _stateID = SCENE_STATE_ID::SUMMON;
    return true;
}

void SummonSceneState::inState()
{
    CCLOG("in summon state...");
}

void SummonSceneState::outState()
{
    CCLOG("out summon state...");
}

void SummonSceneState::onState()
{
    CCLOG("on summon state...");
}

void SummonSceneState::update()
{
    CCLOG("SummonScene updated.");
}

//
// Transitionの定義
//

// toMain
ToMainScene::ToMainScene()
{
}

ToMainScene::~ToMainScene()
{
}

void ToMainScene::transit()
{
}

bool ToMainScene::init()
{
    // test
    _condition = TestCondition::create();
    _condition->retain();
    
    return true;
}

bool ToMainScene::canTransit(State* state)
{
    ValueMap args;
    return (_condition) ? _condition->canTransit(state, args) : false;
}

State* ToMainScene::getNextState() {
    State* main = MainSceneState::create();
    main->retain();
    return main;
}

// toSummon
ToSummonScene::ToSummonScene()
{
}

ToSummonScene::~ToSummonScene()
{
}

bool ToSummonScene::init()
{
    // test
    _condition = TestCondition::create();
    
    return true;
}

void ToSummonScene::transit()
{
}

bool ToSummonScene::canTransit(State* state)
{
    ValueMap args;
    return (_condition) ? _condition->canTransit(state, args) : false;
}

State* ToSummonScene::getNextState() {
    State* main = SummonSceneState::create();
    main->retain();
    return main;
}

//
// TransitionConditionの定義
//

// test
TestCondition::TestCondition()
{
}

TestCondition::~TestCondition()
{
}

bool TestCondition::canTransit(State* state, const ValueMap& args)
{
    return true;
}