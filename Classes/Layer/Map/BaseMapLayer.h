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

#ifndef __LAYER_MAP_BASEMAP_LAYER_H__
#define __LAYER_MAP_BASEMAP_LAYER_H__

#include "cocos2d.h"
#include "GroupMonsterNode.h"
class PlayerStateMenuLayer;
USING_NS_CC;

class BaseMapLayer : public Layer
{
public:
    // implement the "static create()" method manually
   // CREATE_FUNC(BaseMapLayer)

    void bindPlayerStateMenu( PlayerStateMenuLayer * playerStateMenuLayer);
    CC_SYNTHESIZE(int,level_,Level)
protected:
    PlayerStateMenuLayer * player_state_menu_layer_;
    int difficulty_;    // 当前游戏难度
    int wave_;          // 当前游戏的怪物波数
    int totleWave_;     // 当前关卡需要的怪物总波数
    int gold_;          // 当前关卡的金币数量
    int life_;          // 当前关卡的生命数
    int startGold_;     // 当前关卡初始化时金币数量
    int maxLife_;       // 最大生命数量
    unsigned int time_;
    Size win_size_;     // 屏幕大小在初始化时获取
    std::vector<std::vector<Vector<GroupMonsterNode*>>> vector_group_monster_;      // 存储怪物信息的容器
    std::vector<std::vector<std::vector<Point>>> vector_path_;                      // 存储路线的容器

    // 初始化关卡地图
    void initMap();
    // 添加不同地图装饰物
    virtual void addOrnament() = 0;
    // 添加建塔点
    virtual void addTerrains() = 0;
    // 退出
    virtual void onExit() = 0;

    // 加载当前等级的数据，包括初始金币，初始血量，当前关卡的怪物波数，怪物信息等。
    void loadLevelDataFromePlist();
    // 加载怪物移动路径
    void loadPathFromPlist();

};

#endif // __LAYER_MAP_BASEMAP_LAYER_H__
