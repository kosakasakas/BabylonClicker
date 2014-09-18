//
//  ScrollComponentCreator.cpp
//  BabylonClicker
//
//  Created by Takahiro Kosaka on 2014/09/16.
//
//

#include "ScrollComponentCreator.h"
#include "UnicornPlistLoader.h"
#include "BattleController.h"
#include "UnitFactory.h"

Array* ScrollComponentCreator::make()
{
    Array* result = Array::create();
    UnicornPlistLoader* upLoader = new UnicornPlistLoader("revelReleaseList.plist");
    Dictionary* dic = upLoader->getDictionary();
    Array* list = (Array*)(dic->objectForKey("Summon"));
    FieldObject* summonField = dynamic_cast<FieldObject*>(BattleController::getInstance()->getField()->getUserField()->getObjectAtIndex(Field::UFT_Summon));
    for (int i=0,n=summonField->getLevel(); i <= n; ++i) {
        Array* numList = dynamic_cast<Array*>(list->getObjectAtIndex(i));
        Object* it;
        CCARRAY_FOREACH(numList, it)
        {
            String* val = (String*)it;
            UnitFactory* uFactory = new UnitFactory();
            Unit* unit = (Unit*)uFactory->create(val->intValue());
            Node* node = createComponent((UnitData*)unit->getObjectData());
            result->addObject(node);
        }
    }
    return result;
}

Node* ScrollComponentCreator::createComponent(UnitData* ud) {
    Node *node = new Node();
    node->setContentSize(*getComponentSize());
    
    Sprite* frame = Sprite::create("type.png");
    frame->setPosition(Point(40.0, 52.5));
    Sprite* star = Sprite::create("icon_star.png");
    star->setPosition(Point(36.9, 22.3));
    Sprite* soul = Sprite::create("icon_soul.png");
    soul->setPosition(Point(87.7,24.3));
    Sprite* magic = createMagicIconSprite(ud->getMagic());
    magic->setPosition(Point(40.9, 52.8));
    
    Color3B white = Color3B(255,255,255);
    LabelTTF* nameLabel = LabelTTF::create(ud->getName(), "Arial Rounded MT Bold", 12);
    nameLabel->setAnchorPoint(Point(0,0));
    nameLabel->setPosition(Point(61.9, 46.0));
    nameLabel->setColor(white);
    LabelTTF* starLabel = LabelTTF::create(ud->getGrade(), "Arial Rounded MT Bold", 10);
    starLabel->setAnchorPoint(Point(0,0));
    starLabel->setPosition(Point(50.0, 16.2));
    starLabel->setColor(white);
    LabelTTF* soulLabel = LabelTTF::create("1000", "Arial Rounded MT Bold", 12);
    soulLabel->setAnchorPoint(Point(0,0));
    soulLabel->setPosition(Point(99.5, 16.2));
    soulLabel->setColor(white);
    
    node->addChild(frame);
    node->addChild(magic);
    node->addChild(star);
    node->addChild(soul);
    node->addChild(nameLabel);
    node->addChild(starLabel);
    node->addChild(soulLabel);
    
    return node;
}

Size* ScrollComponentCreator::getComponentSize() {
    Size* size = new Size();
    size->setSize(180, 80);
    return size;
}

Sprite* ScrollComponentCreator::createMagicIconSprite(const char* magic) {
    Sprite* sprite;
    Field::MagicFieldType magicType = Field::getMagicFieldType(magic);
    if (magicType == Field::MFT_Dark) {
        sprite = Sprite::create("icon_dark.png");
    } else if (magicType == Field::MFT_Shine) {
        sprite = Sprite::create("icon_light.png");
    } else if (magicType == Field::MFT_Fire) {
        sprite = Sprite::create("icon_fire.png");
    } else if (magicType == Field::MFT_Water) {
        sprite = Sprite::create("icon_water.png");
    } else if (magicType == Field::MFT_Wood) {
        sprite = Sprite::create("icon_leaf.png");
    } else if (magicType == Field::MFT_Wizard) {
        sprite = Sprite::create("icon_light.png");
    }
    return sprite;
}