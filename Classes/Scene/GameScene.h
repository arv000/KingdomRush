#ifndef __SCENE_GAME_SCENE_H__
#define __SCENE_GAME_SCENE_H__
#include "cocos2d.h"

USING_NS_CC;
class GameScene : public Scene
{
public:
    static Scene *createGameScene(int level,int difficulty);

private:
    virtual bool initGame(int level,int difficulty);
};

#endif // __SCENE_GAME_SCENE_H__
