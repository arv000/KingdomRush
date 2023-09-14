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

#ifndef __SCENE_CHOOSE_DIFFICULTY_SCENE_H__
#define __SCENE_CHOOSE_DIFFICULTY_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class ChooseDifficultyScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createSceneWithLevel(int level);
    void initWithLevel(int level);
    virtual bool init();
    void initToggle();
    CC_SYNTHESIZE(int,difficulty_,Difficulty)
    CC_SYNTHESIZE(int,level_,Level)
    // implement the "static create()" method manually
    CREATE_FUNC(ChooseDifficultyScene)


    protected:

        Label *label_blue_;
        Label *label_black_;

        Sprite *sprite_star1;
        Sprite *sprite_star2;
        Sprite *sprite_star3;
        Sprite *sprite_star4;   // 盾牌
        Sprite *sprite_star5;   // 拳头

        std::string str_blue_top_;
        std::string str_blue_[3];
        std::string str_black_[3];

        // 用于记录屏幕的大小
        Size visible_size_;

        MenuItemToggle* toggle_item1_;
        MenuItemToggle* toggle_item2_;
        MenuItemToggle* toggle_item3_;


        void touchStarMenu1(Ref* pSpender);
        void touchStarMenu2(Ref* pSpender);
        void touchStarMenu3(Ref* pSpender);

        void touchReturnMapSenec(Ref* pSpender);
        void touchPlayGame(Ref* pSpender);
};

#endif // __LOADING_SCENE_H__
