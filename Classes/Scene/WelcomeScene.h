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

#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(WelcomeScene)
        void initBackGround(); //  初始化背景图
        void initLogo();        // 初始化 Logo图
        void initMemuSave();    // 初始化记录菜单
        void initButtonCredit(); // 初始化Credit按钮
        void initButtonStart(); // 初始化start 按钮

        // 初始化声音按钮
        void initSoundButton();

        // 初始化LogoAnimation(); logo 动画效果
        void initLogoAnimation();

        // 初始化开始按钮动画
        void initButtonStartAnimation();

        // 初始化Credit动画
        void initButtonCreditAnimation();

        // 设置menu save精灵可见
        void setSpriteMenuSaveVisible();

        // 设置menu save精灵不可见
        void setSpriteMenuSaveInvisable();
private:

        // 用于记录屏幕的大小
        Size visible_size_;
        // 记录logo的位置，有一些精灵需要通过该位置设置其相对位置。
        Point point_logo_;
        // 标志精灵
        Sprite * sprite_logo_;
        // 精灵
        Sprite* sprite_menu_save_;

        MenuItemSprite* sprite_menu_save_close_;
        // 保存菜单关闭按钮
        Point point_menu_save_close_;

        Point point_menu_save_;
        // 游戏开始按钮
        Sprite* sprite_button_start_;

        // credit按钮
        Sprite* sprite_button_credit_;

        // 背映音乐按钮精灵
        Sprite* sprite_background_music_;

        // 背景音效按钮精灵
        Sprite* sprite_background_effect_;
        // 初始化按钮消息
        void intiEvent();

        void initButtonStartEvent();

        bool touchBeganButtonStart(Touch *touch,Event *event);

        bool touchEndedButtonStart(Touch *touch,Event *event);

        void touchMenuSaveClose(cocos2d::Ref *pSender);

        void initBackgroundMusicEvent();
        // 处理背景音乐鼠标点击事件
        bool touchBeganBackgroundMusic(Touch *touch,Event *event);
        // 处理背景音乐鼠标弹起事件
        bool touchEndedBackgroundMusic(Touch *touch,Event *event);

        void initBackgroundEffectEvent();
        // 处理背景音效鼠标点击事件
        bool touchBeganBackgroundEffect(Touch *touch,Event *event);
        // 处理背景音效鼠标弹起事件
        bool touchEndedBackgroundEffect(Touch *touch,Event *event);

        void initKeyEvent();
        // 处理按键按下事件
        void onKeyRelease(EventKeyboard::KeyCode keyCode,Event *event);

        void onEnterTransitionDidFinish();
};

#endif // __WELCOME_SCENE_H__
