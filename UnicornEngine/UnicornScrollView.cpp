//
//  UnicornScrollView.cpp
//  BabylonClicker
//
//  Created by 小坂 昂大 on 2014/09/06.
//
//

#include "UnicornScrollView.h"
#include "UnicornScrollableMenu.h"

const float UnicornScrollView::MIN_DISTANCE = 10;

UnicornScrollView::UnicornScrollView(Menu* menu)
: ScrollView::ScrollView()
, menu(NULL)
{
    //setMenu(menu);
}

UnicornScrollView* UnicornScrollView::create(Menu* menu) {
    UnicornScrollView* pRet = new UnicornScrollView(menu);
    if (pRet && pRet->init())
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

UnicornScrollView* UnicornScrollView::create(Size size, Node* container, Menu* menu)
{
    UnicornScrollView* pRet = new UnicornScrollView(menu);
    if (pRet && pRet->initWithViewSize(size, container))
    {
        pRet->autorelease();
    }
    else
    {
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}



bool UnicornScrollView::init() {
    if ( !ScrollView::init() ) {
        return false;
    }
    return true;
}

bool UnicornScrollView::onTouchBegan(Touch* touch, Event* event) {
    CCLOG("UnicornScrollView onTouchBegan called.");
    pressPoint = touch->getLocationInView();
    if (menu && !waitingTouchEnd) {
        waitingTouchEnd = menu->onTouchBegan(touch, event);
    }
    return ScrollView::onTouchBegan(touch, event);
}

void UnicornScrollView::onTouchCancelled(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        menu->onTouchCancelled(touch, event);
        waitingTouchEnd = false;
    }
    ScrollView::onTouchCancelled(touch, event);
}

void UnicornScrollView::onTouchEnded(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(pressPoint);
        if (distance < MIN_DISTANCE) {
            menu->onTouchEnded(touch, event);
        } else {
            menu->onTouchCancelled(touch, event);
        }
        waitingTouchEnd = true;
    }
    ScrollView::onTouchEnded(touch, event);
}

void UnicornScrollView::onTouchMoved(Touch* touch, Event* event) {
    if (menu && waitingTouchEnd) {
        Point endPoint = touch->getLocationInView();
        float distance = endPoint.getDistance(pressPoint);
        if (distance < MIN_DISTANCE) {
            menu->onTouchMoved(touch, event);
        } else {
            menu->onTouchCancelled(touch, event);
            waitingTouchEnd = false;
        }
    }
    ScrollView::onTouchMoved(touch, event);
}

void UnicornScrollView::addTouchListener() {
    if (_touchListener != nullptr) {
        return;
    }
    auto dispatcher = EventDispatcher::getInstance();
    if( getTouchMode() == Touch::DispatchMode::ALL_AT_ONCE )
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ALL_AT_ONCE);
        
        listener->onTouchBegan = CC_CALLBACK_2(UnicornScrollView::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(UnicornScrollView::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(UnicornScrollView::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(UnicornScrollView::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kUnicornScrollViewPriority);
        _touchListener = listener;
    }
    else
    {
        // Register Touch Event
        auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
        listener->setSwallowTouches(isSwallowsTouches());
        
        listener->onTouchBegan = CC_CALLBACK_2(UnicornScrollView::onTouchBegan, this);
        listener->onTouchMoved = CC_CALLBACK_2(UnicornScrollView::onTouchMoved, this);
        listener->onTouchEnded = CC_CALLBACK_2(UnicornScrollView::onTouchEnded, this);
        listener->onTouchCancelled = CC_CALLBACK_2(UnicornScrollView::onTouchCancelled, this);
        
        dispatcher->addEventListenerWithFixedPriority(listener, kUnicornScrollViewPriority);
        _touchListener = listener;
    }
}

void UnicornScrollView::setMenu(Menu *menu) {
    this->menu = menu;
    UnicornScrollableMenu* scrollableMenu = dynamic_cast<UnicornScrollableMenu*>(menu);
    if(scrollableMenu) {
        scrollableMenu->setValidTouchRectInWorldSpace(getViewRect());
    }
}