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
    CREATE_FUNC(WelcomeScene);
        //  初始化背景图
        void initBackGround();
        // 初始化 Logo图
        void initLogo();
        // 初始化记录菜单
        void initMemuSave();
        // 初始化Credit按钮
        void initButtonCredit();
        // 初始化start 按钮
        void initButtonStart();
        // 初始化声音按钮
        void initSoundButton();
        // 初始化LogoAnimation();
        void initLogoAnimation();


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

        Point point_menu_save_close_;

        Point point_menu_save_;
        // 游戏开始按钮
        Sprite* sprite_button_start_;

        //
        Sprite* sprite_button_credit_;



        void onEnterTransitionDidFinish();
};

#endif // __WELCOME_SCENE_H__
