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

#include "GameMenuLayer.h"


// on "init" you need to initialize your instance
bool GameMenuLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    isFirst =  true;
    // 获取窗口大小
    auto winSize = Director::getInstance()->getWinSize();

    // 商店精灵
    shop_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butShop_0001.png"),
                                   Sprite::createWithSpriteFrameName("butShop_0002.png"),
                                   CC_CALLBACK_1(GameMenuLayer::touchShop,this));
    // 百科全书精灵
    book_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butEncyclopedia_0001.png"),
                                   Sprite::createWithSpriteFrameName("butEncyclopedia_0002.png"),
                                   CC_CALLBACK_1(GameMenuLayer::touchBook,this));
    // 升级精灵
    update_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("butUpgrades_0001.png"),
                                    Sprite::createWithSpriteFrameName("butUpgrades_0002.png"),
                                    CC_CALLBACK_1(GameMenuLayer::touchUpdate,this));

    book_->setPosition(Point(winSize.width - book_->getContentSize().width/2,book_->getContentSize().height/2 -130));
    update_->setPosition(Point(book_->getPosition().x - 160 , update_->getContentSize().height/2-130));
    shop_->setPosition(Point(update_->getPosition().x - 160 , shop_->getContentSize().height/2-130));

    auto menu = Menu::create(shop_,update_,book_,nullptr);
    menu->setPosition(Vec2::ZERO);
    addChild(menu);

    sprite_map_stars_container_ = Sprite::createWithSpriteFrameName("mapStarsContainer.png");
    sprite_map_stars_container_->setPosition(Point(winSize.width - sprite_map_stars_container_->getContentSize().width/2 - 10,
                                                   winSize.height - sprite_map_stars_container_->getContentSize().height/2 + 60));
    addChild(sprite_map_stars_container_);

    // 星星的数量
    lable_star_ = Label::createWithTTF("0","SohoGothicProMedium.ttf",26);
    lable_star_->setPosition(Point(sprite_map_stars_container_->getContentSize().width/4*3 + 20,sprite_map_stars_container_->getContentSize().height/2));
    sprite_map_stars_container_->addChild(lable_star_);

    // 砖石的数量
    lable_diamonds_  = Label::createWithTTF("0","SohoGothicProMedium.ttf",26);
    lable_diamonds_->setPosition(Point(sprite_map_stars_container_->getContentSize().width/4,sprite_map_stars_container_->getContentSize().height/2));
    sprite_map_stars_container_->addChild(lable_diamonds_);

    return true;
}

void GameMenuLayer::touchBook(Ref *pSender)
{

}

void GameMenuLayer::touchShop(Ref *pSender)
{

}

void GameMenuLayer::touchUpdate(Ref *pSender)
{

}

void GameMenuLayer::onEnterTransitionDidFinish()
{
    if(isFirst){
        book_->runAction(MoveBy::create(0.3f,Point(0,130)));
        update_->runAction(MoveBy::create(0.3f,Point(0,130)));
        shop_->runAction(MoveBy::create(0.3f,Point(0,130)));

        sprite_map_stars_container_->runAction(MoveBy::create(0.3f,Point(0,-70)));
        isFirst = false;
    }
}

