#include "MapFlagSprite.h"
#include "../Layer/GameLayer.h"
#include "../Scene/ChooseDifficultyScene.h"
MapFlagSprite::MapFlagSprite(){}

MapFlagSprite::~MapFlagSprite(){}

bool MapFlagSprite::initWithLevel(int level)
{
    setLevel(level);
    if(!Sprite::init()){
        return false;
    }
    auto wings = Sprite::createWithSpriteFrameName("mapFlag_wings_0015.png");
    addChild(wings);
    sprite_flag_ = Sprite::createWithSpriteFrameName("mapFlag_0112.png");
    addChild(sprite_flag_);

    initEvent();
    return true;
}

MapFlagSprite *MapFlagSprite::createWithLevel(int level)
{
    auto mapFlagSprite = new MapFlagSprite();
    // 创建存储按钮
    if(mapFlagSprite && mapFlagSprite->initWithLevel(level)){
        mapFlagSprite->autorelease();
        return mapFlagSprite;
    }
    CC_SAFE_DELETE(mapFlagSprite);
    return nullptr;
}

void MapFlagSprite::initEvent()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(MapFlagSprite::onTouchBeganFlag,this);
    listener->onTouchEnded = CC_CALLBACK_2(MapFlagSprite::onTouchEndedFlag,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,sprite_flag_);
}

bool MapFlagSprite::onTouchBeganFlag(Touch *touch, Event *event)
{

}

bool MapFlagSprite::onTouchEndedFlag(Touch *touch, Event *event)
{
    auto target = static_cast<Sprite*>(event->getCurrentTarget());

    Point p = target->convertTouchToNodeSpace(touch);
    Rect rect= Rect(0,0,target->getContentSize().width,target->getContentSize().height);
    if(rect.containsPoint(p)){
         CCLOG(" MapFlagSprite::onTouchEndedFlag start level:%d",getLevel());
         Director::getInstance()->pushScene(ChooseDifficultyScene::createSceneWithLevel(getLevel()));
    }
    return false;
}
