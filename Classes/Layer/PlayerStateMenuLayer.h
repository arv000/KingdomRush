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

#ifndef __LAYER_PLAYER_STATE_MENU_LAYER_H__
#define __LAYER_PLAYER_STATE_MENU_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class PlayerStateMenuLayer : public Layer
{
public:
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(PlayerStateMenuLayer)
    // 获取或者设置当前关卡的等级
    CC_SYNTHESIZE(int,level_,Level)
    // 获取或者展示当前关卡的难度
    CC_SYNTHESIZE(int,difficult_,Difficult)
    // 设置当前生命值接口
    void setLife(int life);
    // 设置当前金币值接口
    void setGold(int gold);
    // 设置怪物波数接口
    void setWave(int thisWave,int tolalWave);
private:
    Size win_size_;
    Sprite * sprite_state_;
    Sprite * sprite_pause_;
    Label *label_life_;
    Label* label_gold_;
    Label* label_wave_;

    Sprite* sprite_thunder_stone_;  // 雷石
    Sprite* sprite_paratrooper_;    // 伞兵
    Sprite* sprite_pack_;           // 锦囊
    Sprite* sprite_back_pack_;      // 锦囊背景。六侠背景
    // 六侠
    Sprite* sprite_backPack_icons_[6];
    std::string stringForSkillFileName;
    //
    ProgressTimer *timer_stone_;
    ProgressTimer *timer_paratrooper_;
    // ===== 精灵响应函数 =========
    // 监听暂停精灵
    bool onTouchBeganSpirtePause(Touch* touch,Event *event);
    void onTouchEnedSpirtePause(Touch* touch,Event *event);

    // 监听雷石精灵
    bool onTouchBeganSpriteThunderStone(Touch* touch,Event *event);
    void onTouchEnedSSpriteThunderStone(Touch* touch,Event *event);

    // 监听伞兵 精灵
    bool onTouchBeganSpriteParatrooper(Touch* touch,Event *event);
    void onTouchEnedSSpriteParatrooper(Touch* touch,Event *event);

    // 监听锦囊 精灵
    bool onTouchBeganSpritePack(Touch* touch,Event *event);
    void onTouchEnedSSpritePack(Touch* touch,Event *event);

    void onEnterTransitionDidFinish();
     // 初始化
    void initSprite();
    void initEvent();

};

#endif // __LAYER_PLAYER_STATE_MENU_LAYER_H__
