//
//  GameObject.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/08/14.
//
//

#include "GameObject.h"
#include "GameController.h"

GameObject::GameObject()
: level(0)
, cost(0)
, objectID(0)
{
}

GameObject::~GameObject()
{
}

bool GameObject::canPurchase() {
    int soul = GameController::getInstance()->getUser()->getSoul();
    return (cost <= soul) ? true : false;
}

bool GameObject::canSacrifice() {
    return true;
}

bool GameObject::canSummon() {
    return (canPurchase() && canSacrifice()) ? true : false;
}

void GameObject::purchase() {
    if (canSacrifice()) {
        GameController::getInstance()->getUser()->reduceSoul(cost);
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

void GameObject::dump() {
    CCLOG("======GameObject Class======");
    CCLOG("level: %d", level);
    CCLOG("cost: %d", cost);
    CCLOG("objectID: %d", objectID);
    CCLOG("canPurchase: %d", canPurchase());
    CCLOG("canSacriface: %d", canSacrifice());
    CCLOG("canSummon: %d", canSummon());
}