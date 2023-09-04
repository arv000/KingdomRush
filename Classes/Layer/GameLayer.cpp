/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameLayer.h"
#include "GameMenuLayer.h"
#include "../Sprite/MapFlagSprite.h"
USING_NS_CC;

Scene* GameLayer::createScene()
{
    auto scene = Scene::create();
    auto game_layer = GameLayer::create();
    auto game_menu_layer = GameMenuLayer::create();
    scene->addChild(game_layer);
    scene->addChild(game_menu_layer);
    return scene;
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    win_size_ = Director::getInstance()->getWinSize();
    sprite_background_ = Sprite::createWithSpriteFrameName("MapBackground.png");
    sprite_background_->setAnchorPoint(Vec2::ZERO);
    sprite_background_->setPosition(Vec2::ZERO);
    addChild(sprite_background_);
    initMapFlagPoint();
    initMapFlag();
    initRoad();
    initEvent();

    return true;
}

void GameLayer::initMapFlagPoint()
{
    // 一共12个关卡，优先设置各个关卡标识的位置，
    vector_map_flag_point_.push_back(Point(375,775));
    vector_map_flag_point_.push_back(Point(495,735));
    vector_map_flag_point_.push_back(Point(510,620));
    vector_map_flag_point_.push_back(Point(370,575));
    vector_map_flag_point_.push_back(Point(205,505));
    vector_map_flag_point_.push_back(Point(455,305));
    vector_map_flag_point_.push_back(Point(690,420));
    vector_map_flag_point_.push_back(Point(855,254));
    vector_map_flag_point_.push_back(Point(1020,340));
    vector_map_flag_point_.push_back(Point(934,490));
    vector_map_flag_point_.push_back(Point(830,560));
    vector_map_flag_point_.push_back(Point(795,710));
    vector_map_flag_point_.push_back(Point(910,770));
    vector_map_flag_point_.push_back(Point(1015,770));
}

void GameLayer::initMapFlag()
{
    for(int i = 0 ; i < 13; i ++){
        auto mapFlag = MapFlagSprite::createWithLevel(i);
        mapFlag->setPosition(vector_map_flag_point_.at(i));
        addChild(mapFlag);
    }
}

void GameLayer::initRoad()
{
    sprite_road_ = RoadSprite::create();
    sprite_road_->setPosition(Point(635,500));
    addChild(sprite_road_);
}

void GameLayer::initEvent()
{
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesMoved = CC_CALLBACK_2(GameLayer::onTouchesMoved,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener,sprite_background_);


}

void GameLayer::onTouchesMoved(const std::vector<Touch *> &touches, Event *evet)
{
    // 单点时，touches中只有一个Touch对象，所以通过touches[0]就可以得到触摸对象
           auto touch = touches[0];
           // 计算滑动过程中的滑动增量
           auto diff = touch->getDelta();
           // 得到当前bgSprite的位置
           auto currentPos = this->getPosition();
           // 得到滑动后bgSprite应该所在的位置
           auto pos = currentPos + diff;
           // 得到此刻bgSprite的尺寸
           auto bgSpriteCurrSize = sprite_background_->getBoundingBox().size;

           //边界控制，约束pos的位置
           pos.x = MIN(pos.x, bgSpriteCurrSize.width * sprite_background_->getAnchorPoint().x);
           pos.x = MAX(pos.x, -bgSpriteCurrSize.width + win_size_.width + bgSpriteCurrSize.width * sprite_background_->getAnchorPoint().x);
           pos.y = MIN(pos.y, bgSpriteCurrSize.height * sprite_background_->getAnchorPoint().y);
           pos.y = MAX(pos.y, -bgSpriteCurrSize.height + win_size_.height + bgSpriteCurrSize.height * sprite_background_->getAnchorPoint().y);

           this->setPosition(pos);
}

void GameLayer::onEnterTransitionDidFinish()
{
    sprite_road_->runActionRoadAnimation(1);
}

