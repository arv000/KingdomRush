#ifndef _Node_GROUP_MONSTER_NODE_H_
#define _Node_GROUP_MONSTER_NODE_H_

#include "cocos2d.h"
USING_NS_CC;

class GroupMonsterNode : public Node {

public:
    static GroupMonsterNode *initGroupEnemy(int type,int road,int path);
    CREATE_FUNC(GroupMonsterNode)
        // 保存怪物的类型
        CC_SYNTHESIZE(int,type_,Type)
        // 保存怪物的出口
        CC_SYNTHESIZE(int,road_,Road)
        // 保存怪物的路线
        CC_SYNTHESIZE(int,path_,Path)
};

#endif  // _Node_GROUP_MONSTER_NODE_H_
