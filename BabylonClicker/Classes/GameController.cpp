//
//  GameController.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2015/03/27.
//
//

#include "GameController.h"

#define GAME_LOGIC_UPDATE_INTERVAL     15   // ゲームロジック更新頻度(fps)
#define RENDERING_SYS_UPDATE_INTERVAL  60   // 描画システム更新頻度(fps)

const int GameController::animationInterval = 60; // ゲーム全体の更新頻度(fps)
GameController* GameController::_singleton = nullptr;

GameController::GameController()
: _sceneStateMap(nullptr)
, _root(nullptr)
{
}

GameController::~GameController()
{
    _sceneStateMap->release();
}

GameController* GameController::getInstatnce() {
    if( nullptr == _singleton) {
        _singleton = GameController::create();
    }
    return _singleton;
}

bool GameController::init()
{
    _sceneStateMap = SceneStateMap::create();
    _sceneStateMap->retain();
    
    return true;
}

void GameController::updateRenderingSystem(float dt) {
}

void GameController::updateGameLogic(float dt) {
    _sceneStateMap->update();
}

void GameController::setRootLayer(Layer* scene) {
    // タイマーはシーン依存なので、シーンを入れ替えたらコールバックを再定義する。
    if (_root) {
        _root->unscheduleAllCallbacks();
        _root->release();
    }
    _root = scene;
    _root->retain();
    
    float gameLogicUpdateRate = 1.0f / GAME_LOGIC_UPDATE_INTERVAL;
    float renderingUpdateRate = 1.0f / RENDERING_SYS_UPDATE_INTERVAL;
    
    _root->schedule(schedule_selector(GameController::updateGameLogic), gameLogicUpdateRate);
    _root->schedule(schedule_selector(GameController::updateRenderingSystem), renderingUpdateRate);
}