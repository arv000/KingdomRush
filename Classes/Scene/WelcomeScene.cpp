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

#include "WelcomeScene.h"

USING_NS_CC;


Scene* WelcomeScene::createScene()
{
    return WelcomeScene::create();
}


// on "init" you need to initialize your instance
bool WelcomeScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    visible_size_ = Director::getInstance()->getVisibleSize();

    initBackGround();
    initLogo();
    initMemuSave();
    initButtonStart();
    initButtonCredit();
    initSoundButton();

    return true;

}

void WelcomeScene::initBackGround()
{

    auto sprite_background = Sprite::createWithSpriteFrameName("mainmenu_bg.png");

    sprite_background->setPosition(Point(visible_size_.width/2,visible_size_.height/2));
    sprite_background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    // -1表示插入无论有几个节点都在最底层。ZOrder默认值是0。
    addChild(sprite_background,-1);
}

void WelcomeScene::initLogo()
{
     // 加载 Logo.png 图片
    sprite_logo_ =  Sprite::createWithSpriteFrameName("logo.png");
    sprite_logo_->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    // 设置Logo屏幕局中，居上
    // 设置logo.png的坐标为左右居中
    point_logo_.x = visible_size_.width/2;
    // 设置Logo局上（顶着上面排放）
    point_logo_.y = visible_size_.height - (sprite_logo_->getContentSize().height/2);
    // 初始化效果为0.2f,初始化为缩小状态，图片加载完使其变大，有弹出效果。
    sprite_logo_->setScale(1.0f);
    sprite_logo_->setPosition(point_logo_);
    addChild(sprite_logo_);
}

void WelcomeScene::initMemuSave()
{
    sprite_menu_save_ = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
    point_menu_save_.x = point_logo_.x;
    point_menu_save_.y = point_logo_.y - sprite_logo_->getContentSize().height*1.4/2;
    sprite_menu_save_->setPosition(point_menu_save_);
    addChild(sprite_menu_save_,0);

    sprite_menu_save_close_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png"),
                                                     Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0002.png"));
    point_menu_save_close_.x = point_logo_.x;
    point_menu_save_close_.y = point_menu_save_.y - sprite_menu_save_->getContentSize().height/2 + sprite_menu_save_close_->getContentSize().height/2;
    sprite_menu_save_close_->setPosition(point_menu_save_close_);

    auto menu = Menu::create(sprite_menu_save_close_,nullptr);
     menu->setPosition(Vec2::ZERO);
     addChild(menu,0);
}

void WelcomeScene::initButtonCredit()
{
    sprite_button_credit_= Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
    sprite_button_credit_->setPosition(point_logo_.x,point_logo_.y- 180) ;
    addChild(sprite_button_credit_,0);
}

void WelcomeScene::initButtonStart()
{
    sprite_button_start_ = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    sprite_button_start_->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprite_button_start_->setPosition(point_logo_.x,point_logo_.y);
    addChild(sprite_button_start_,1);
}

void WelcomeScene::initSoundButton()
{

}

void WelcomeScene::initLogoAnimation()
{

}

// 过渡动画播放完毕后，该方法会被自动调用。
void WelcomeScene::onEnterTransitionDidFinish()
{
    log("onEnterTransitionDidFinish");
}
