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

    intiEvent();
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
    sprite_logo_->setScale(0.2f);
    sprite_logo_->setPosition(point_logo_);
    addChild(sprite_logo_,9);
}

void WelcomeScene::initMemuSave()
{
    sprite_menu_save_ = Sprite::createWithSpriteFrameName("mainmenu_saveslot_bg.png");
    point_menu_save_.x = point_logo_.x;
    point_menu_save_.y = point_logo_.y - sprite_logo_->getContentSize().height*0.7;
    sprite_menu_save_->setPosition(Point(point_menu_save_.x ,point_menu_save_.y - 500));
    addChild(sprite_menu_save_,0);

    sprite_menu_save_close_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0001.png"),
                                                     Sprite::createWithSpriteFrameName("mainmenu_saveslot_close_0002.png"),
                                                     CC_CALLBACK_1(WelcomeScene::touchMenuSaveClose,this));
    point_menu_save_close_.x = point_logo_.x;
    point_menu_save_close_.y = point_menu_save_.y - sprite_menu_save_->getContentSize().height/2 + sprite_menu_save_close_->getContentSize().height;
    sprite_menu_save_close_->setPosition(Point(point_menu_save_close_.x ,point_menu_save_close_.y - 500));

    auto menu = Menu::create(sprite_menu_save_close_,nullptr);
     menu->setPosition(Vec2::ZERO);
     addChild(menu,0);
}

void WelcomeScene::initButtonCredit()
{
    sprite_button_credit_= Sprite::createWithSpriteFrameName("menu_creditschain_0001.png");
    sprite_button_credit_->setPosition(point_logo_.x,point_logo_.y- 180) ;
    sprite_button_credit_->setVisible(false);
    addChild(sprite_button_credit_,0);
}

void WelcomeScene::initButtonStart()
{
    sprite_button_start_ = Sprite::createWithSpriteFrameName("menu_startchain_0001.png");
    sprite_button_start_->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    // 设置隐藏在播放动画的时候将其显示出来。
    sprite_button_start_->setVisible(false);
    sprite_button_start_->setPosition(point_logo_.x,point_logo_.y);
    addChild(sprite_button_start_,1);
}

void WelcomeScene::initSoundButton()
{
    auto winSize = Director::getInstance()->getWinSize();
    sprite_background_music_ = Sprite::createWithSpriteFrameName("options_overlay_buttons_0001.png");
    Point point_background_music;
    point_background_music.x = sprite_background_music_->getContentSize().width/2 + 10;
    point_background_music.y= winSize.height - sprite_background_music_->getContentSize().height/2 -10;
    // 设置背景音乐按钮位置
    sprite_background_music_->setPosition(point_background_music);
    addChild(sprite_background_music_);

    sprite_background_effect_ = Sprite::createWithSpriteFrameName("options_overlay_buttons_0003.png");
    Point point_background_effect;
    point_background_effect.x = point_background_music.x+sprite_background_music_->getContentSize().width;
    point_background_effect.y = winSize.height - sprite_background_effect_->getContentSize().height/2 -10;
    // 设置背景音效按钮位置
    sprite_background_effect_->setPosition(point_background_effect);
    addChild(sprite_background_effect_);
}

void WelcomeScene::initLogoAnimation()
{
    auto sprite = Sprite::createWithSpriteFrameName("logo_brillo_0001.png");
    sprite->setPosition(point_logo_);
    // 生成祯动画
    SpriteFrame * frame = nullptr;
    Vector<SpriteFrame*> aFrames(20);
    for (int len = 1; len <= 21; len ++) {

        frame  = SpriteFrameCache::getInstance()->getSpriteFrameByName(StringUtils::format("logo_brillo_00%02d.png",len));
        if(nullptr != frame){
            aFrames.pushBack(frame);
        }
    }
    addChild(sprite,10);
    auto animation = Animation::createWithSpriteFrames(aFrames,0.1f);
    sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

// 初始化
void WelcomeScene::initButtonStartAnimation()
{
    sprite_button_start_->setVisible(true);
    // 使得精灵移动
    sprite_button_start_->runAction(MoveTo::create(0.3f,Point(point_logo_.x,point_logo_.y - 180)));
}

void WelcomeScene::initButtonCreditAnimation()
{
    sprite_button_credit_->runAction(
                Sequence::create(
                    DelayTime::create(0.3f),
                    CallFuncN::create(CC_CALLBACK_0(Sprite::setVisible,sprite_button_credit_,true)),
                    MoveTo::create(0.3f,Point(point_logo_.x,point_logo_.y-360)),NULL));
}

void WelcomeScene::setSpriteMenuSaveVisible()
{
    sprite_menu_save_->runAction(MoveTo::create(0.3f,point_menu_save_));
    sprite_menu_save_close_->runAction(MoveTo::create(0.3f,point_menu_save_close_));
}

void WelcomeScene::setSpriteMenuSaveInvisable()
{
    sprite_menu_save_->runAction(MoveTo::create(0.3f,Point(0,-500)));
    sprite_menu_save_close_->runAction(MoveTo::create(0.3f,Point(0,-500)));
}

void WelcomeScene::intiEvent()
{
    initButtonStartEvent();
    initBackgroundMusicEvent();
    initBackgroundEffectEvent();
    initKeyEvent();
}

void WelcomeScene::initButtonStartEvent()
{
    auto autoListener =EventListenerTouchOneByOne::create();
    autoListener->onTouchBegan = CC_CALLBACK_2(WelcomeScene::touchBeganButtonStart,this);
    autoListener->onTouchEnded = CC_CALLBACK_2(WelcomeScene::touchEndedButtonStart,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(autoListener,sprite_button_start_);

}

bool WelcomeScene::touchBeganButtonStart(Touch *touch, Event *event)
{

    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if(sprite->getBoundingBox().containsPoint(touPoint)){
        CCLOG("touchBeganButtonStart");
        sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0002.png"));
        return true;
    }
    return false;
}

bool WelcomeScene::touchEndedButtonStart(Touch *touch, Event *event)
{
     Vec2 touPoint = touch->getLocation();
     auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
     if(sprite->getBoundingBox().containsPoint(touPoint)){
         CCLOG("touchEndedButtonStart");
         sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("menu_startchain_0001.png"));
         sprite_button_credit_->setVisible(false);
         sprite_button_credit_->runAction(MoveTo::create(0.3f,Point(point_logo_.x,point_logo_.y-180)));
         sprite_button_start_->runAction(Sequence::create(
                                             DelayTime::create(0.3f),
                                             MoveTo::create(0.3f,Point(point_logo_.x,point_logo_.y)),NULL));
         sprite_button_start_->setVisible(false);
         setSpriteMenuSaveVisible();
         return true;
     }
     return false;
}

void WelcomeScene::touchMenuSaveClose(Ref *pSender)
{
    setSpriteMenuSaveInvisable();
    initButtonStartAnimation();
    initButtonCreditAnimation();
}

void WelcomeScene::initBackgroundMusicEvent()
{
    auto autoListener =EventListenerTouchOneByOne::create();
    autoListener->onTouchBegan = CC_CALLBACK_2(WelcomeScene::touchBeganBackgroundMusic,this);
    autoListener->onTouchEnded = CC_CALLBACK_2(WelcomeScene::touchEndedBackgroundMusic,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(autoListener,sprite_background_music_);
}

bool WelcomeScene::touchBeganBackgroundMusic(Touch *touch, Event *event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if(sprite->getBoundingBox().containsPoint(touPoint)){
        if(UserDefault::getInstance()->getIntegerForKey("background_music",1) == 1){
            UserDefault::getInstance()->setIntegerForKey("background_music",0);
        }else{
            UserDefault::getInstance()->setIntegerForKey("background_music",1);
        }
        CCLOG("touchBeganButtonStart");
        return true;
    }
    return false;
}

bool WelcomeScene::touchEndedBackgroundMusic(Touch *touch, Event *event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if(sprite->getBoundingBox().containsPoint(touPoint)){
        CCLOG("touchBeganButtonStart");
        if(UserDefault::getInstance()->getIntegerForKey("background_music",1) == 1){
            sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0001.png"));
        }else{
            sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0002.png"));
        }

        return true;
    }
    return false;
}

void WelcomeScene::initBackgroundEffectEvent()
{
    auto autoListener =EventListenerTouchOneByOne::create();
    autoListener->onTouchBegan = CC_CALLBACK_2(WelcomeScene::touchBeganBackgroundEffect,this);
    autoListener->onTouchEnded = CC_CALLBACK_2(WelcomeScene::touchEndedBackgroundEffect,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(autoListener,sprite_background_effect_);
}

bool WelcomeScene::touchBeganBackgroundEffect(Touch *touch, Event *event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if(sprite->getBoundingBox().containsPoint(touPoint)){
        CCLOG("touchBeganButtonStart");
        if(UserDefault::getInstance()->getIntegerForKey("background_effect",1) == 1){
            sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0003.png"));
        }else{
            sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("options_overlay_buttons_0004.png"));
        }
        return true;
    }
    return false;
}

bool WelcomeScene::touchEndedBackgroundEffect(Touch *touch, Event *event)
{
    Vec2 touPoint = touch->getLocation();
    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    if(sprite->getBoundingBox().containsPoint(touPoint)){
        CCLOG("touchEndedBackgroundEffect");
        if(UserDefault::getInstance()->getIntegerForKey("background_effect",1) == 1){
            UserDefault::getInstance()->setIntegerForKey("background_effect",0);
        }else{
            UserDefault::getInstance()->setIntegerForKey("background_effect",1);
        }
        return true;
    }
    return false;
}

void WelcomeScene::initKeyEvent()
{
    auto autoListener =EventListenerKeyboard::create();
    autoListener->onKeyReleased = CC_CALLBACK_2(WelcomeScene::onKeyRelease,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(autoListener,this);
}

void WelcomeScene::onKeyRelease(EventKeyboard::KeyCode keyCode, Event *event)
{
    switch(keyCode){
        case EventKeyboard::KeyCode::KEY_ESCAPE :
            // 需要判断按钮是否处于动画效果过程中，如果是处于动画效果，那么再执行动画可能会出现重画冲突的情况。
            if(!sprite_button_start_->isVisible() && !sprite_button_start_->isRunning()){
                setSpriteMenuSaveInvisable();
                initButtonStartAnimation();
                initButtonCreditAnimation();
            }
            break;
        default:
            break;
    }
}

// 过渡动画播放完毕后，该方法会被自动调用。
void WelcomeScene::onEnterTransitionDidFinish()
{
    log("onEnterTransitionDidFinish");
    auto Sepquence = Sequence::create(ScaleTo::create(0.5f,1.5f,1.5f),
                                      ScaleTo::create(0.2f,1.0f,1.0f),
                                      CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initLogoAnimation,this)),
                                      CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initButtonStartAnimation,this)),
                                      CallFuncN::create(CC_CALLBACK_0(WelcomeScene::initButtonCreditAnimation,this)),
                                      NULL);
    sprite_logo_->runAction(Sepquence);
}
