#ifndef LAYER_MAP_LEVEL0_H
#define LAYER_MAP_LEVEL0_H
#include "cocos2d.h"
#include "BaseMapLayer.h"
USING_NS_CC;

class Level0 : public BaseMapLayer
{
public:
    Level0();
    ~Level0();
    // 根据难度创建游戏
    static Level0 *createGame(int difficulty);
private:
    virtual bool initWithDifficulty(int difficulty);

    // BaseMapLayer interface
protected:
    void addOrnament();
    void addTerrains();
    void onExit();
};

#endif // LEVEL0_H
