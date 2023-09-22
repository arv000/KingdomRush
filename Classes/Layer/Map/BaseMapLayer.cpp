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

#include "BaseMapLayer.h"
#include "../PlayerStateMenuLayer.h"
USING_NS_CC;

void BaseMapLayer::bindPlayerStateMenu(PlayerStateMenuLayer *playerStateMenuLayer)
{
    player_state_menu_layer_ = playerStateMenuLayer;
}

void BaseMapLayer::initMap()
{
    loadLevelDataFromePlist();
    loadPathFromPlist();
}
// 加载当前等级的数据，包括初始金币，初始血量，当前关卡的怪物波数，怪物信息等。
// 读取plist文件，文件中包含了初始化信息
void BaseMapLayer::loadLevelDataFromePlist()
{
    auto fileUtils = FileUtils::getInstance();
    std::string file_path = fileUtils->fullPathForFilename(StringUtils::format("plist/level%d_%d_monsters.plist",getLevel(),difficulty_));
    if(fileUtils->isFileExist(file_path)){
          ValueMap dataMap = fileUtils->getValueMapFromFile(file_path);
          auto data_array  =  dataMap.at("data").asValueVector();
          ValueMap  data = data_array.at(0).asValueMap();
          // 读取初始金币值
          startGold_ = data.at("gold").asInt();
          maxLife_ = data.at("life").asInt();
          totleWave_ = data.at("wave").asInt();
          // 怪物信息列表
          auto monsters_array  =  dataMap.at("monsters").asValueVector();
          std::vector<Vector<GroupMonsterNode*>> thisTimeMonster;
          CCLOG("monsters_array size,%zu",monsters_array.size());
          // 遍历每一波的信息，monsters_array.size的大小等于
          for(auto monsters:monsters_array){
              // 每一波，可以分很多次出怪物 ，遍历在当前波的所以次数怪物的信息
              for(auto monsters_wave:monsters.asValueVector()){
                Vector<GroupMonsterNode*> monsterVector;
                // 遍历当前次的怪物信息
                auto monsters_wave_lists = monsters_wave.asValueVector();
                for (auto item : monsters_wave_lists) {
                    // 获取当前一波，中每一次出兵时，所以怪物的信息，包括怪物的类型，路线，等
                    ValueMap monsters_item = item.asValueMap();
                    monsterVector.pushBack(GroupMonsterNode::initGroupEnemy(
                                               monsters_item.at("type").asInt(),
                                               monsters_item.at("road").asInt(),
                                               monsters_item.at("path").asInt()
                                               ));

                }
                thisTimeMonster.push_back(monsterVector);
                monsters_wave_lists.clear();
              }
              vector_group_monster_.push_back(thisTimeMonster);
              thisTimeMonster.clear();
          }
    }
    else {
        CCLOG("文件不存在");
    }
}
// 加载怪物移动路径
void BaseMapLayer::loadPathFromPlist()
{
    auto fileUtils = FileUtils::getInstance();
    std::string file_path = fileUtils->fullPathForFilename(StringUtils::format("plist/level%d_paths.plist",getLevel()));
    if(fileUtils->isFileExist(file_path)){
          ValueMap dataMap = fileUtils->getValueMapFromFile(file_path);
          ValueVector paths_array = dataMap.at("paths").asValueVector();
          // 遍历每一关卡中的路线
          for(auto wave_item:paths_array){
            std::vector<std::vector<Point>> tempPathVector;
              auto wave_array = wave_item.asValueVector();
              // 遍历每一波的路线
              for(auto item : wave_array){
                  // 遍历每个路线的坐标
                  std::vector<Point> tempRandomPathVector;
                  for(auto point_array:item.asValueVector()){
                        auto point_item = point_array.asValueMap();
                        Point tempPoint= Point();
                        CCLOG("x:%f,y:%f;",point_item.at("x").asFloat(),point_item.at("y").asFloat());
                        tempPoint.x = point_item.at("x").asFloat()*1.15;
                        tempPoint.y = point_item.at("y").asFloat()*1.20+50;
                        tempRandomPathVector.push_back(tempPoint);
                  }
                  tempPathVector.push_back(tempRandomPathVector);
                  tempRandomPathVector.clear();
              }
            vector_path_.push_back(tempPathVector);
            tempPathVector.clear();
          }
    }else{
          CCLOG("path文件不存在");
    }
}
