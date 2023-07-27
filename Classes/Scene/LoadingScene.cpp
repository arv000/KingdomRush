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

#include "LoadingScene.h"

USING_NS_CC;


Scene* LoadingScene::createScene()
{
    return LoadingScene::create();
}


// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    numberOfLoadedRes = 0;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto background = Sprite::create("Loadding.png");
    background->setRotation(-90.0f);
    background->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    addChild(background);
    // 定时更新，用于检测资源是否被加载完成，如果加载完成才跳入到正真的欢迎页面。
    schedule(CC_SCHEDULE_SELECTOR(LoadingScene::logic),1.0f);
    return true;

}
// 该代码处理加载资源的操作。
// 加载资源包括图片，声音等。
void LoadingScene::loadSource(){

}
void LoadingScene::logic(float dt)
{
     // 如果你愿意可以在这里通过监听numberOfLoadedRes的值来显示加载进度。
    if(0 == numberOfLoadedRes){
        loadSource();
    }else if(100 == numberOfLoadedRes){
        // 处理跳转动作。
    }
}
