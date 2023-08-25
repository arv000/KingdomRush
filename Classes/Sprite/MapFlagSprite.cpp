#include "MapFlagSprite.h"
#include "../Layer/GameLayer.h"
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
