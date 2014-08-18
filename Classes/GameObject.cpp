//
//  GameObject.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "GameObject.h"
#include "GameController.h"

GameObject::GameObject(ObjectData* data)
{
    objectData = data;
}

GameObject::~GameObject()
{
    objectData->release();
}

bool GameObject::canPurchase() const{
    int soul = GameController::getInstance()->getUser()->getSoul();
    return (objectData->getCost() <= soul) ? true : false;
}

bool GameObject::canSacrifice() const{
    return true;
}

bool GameObject::canSummon() const{
    return (canPurchase() && canSacrifice()) ? true : false;
}

void GameObject::purchase() const{
    if (canSacrifice()) {
        GameController::getInstance()->getUser()->reduceSoul(objectData->getCost());
    } else {
        CCLOG("con not pay summon cost!");
    }
}

void GameObject::sacrifice() {
    CCLOG("needless to sacrifice.");
}

void GameObject::summon() {
    if (canSacrifice()) {
        // notify to UnitCage.
        CCLOG("summon successfully!!");
    }
}

void GameObject::dump() const{
    CCLOG("======GameObject Class======");
    CCLOG("canPurchase: %d", canPurchase());
    CCLOG("canSacriface: %d", canSacrifice());
    CCLOG("canSummon: %d", canSummon());
    CCLOG("objectData RetainCount: %d", objectData->retainCount());
    objectData->dump();
}