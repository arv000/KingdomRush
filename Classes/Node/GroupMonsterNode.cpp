#include "GroupMonsterNode.h"

GroupMonsterNode *GroupMonsterNode::initGroupEnemy(int type, int road, int path)
{
    auto monster = new GroupMonsterNode();
    if(monster && monster->init()){
        monster->setType(type);
        monster->setRoad(road);
        monster->setPath(path);
        return monster;
    }
    CC_SAFE_FREE(monster);
    return nullptr;
}
