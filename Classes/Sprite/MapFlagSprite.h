#ifndef _SPRITE_MAP_FLAG_SPRITE_H_
#define _SPRITE_SLOT_MENU_SPRITE_H_

#include "cocos2d.h"
USING_NS_CC;

class MapFlagSprite : public Sprite {

public:
    MapFlagSprite();
    ~MapFlagSprite();
    virtual bool initWithLevel(int num);
    CREATE_FUNC(MapFlagSprite)
    static MapFlagSprite *createWithLevel(int num);

    void initEvent();
    bool onTouchBeganFlag(Touch* touch,Event *event);
    bool onTouchEndedFlag(Touch* touch,Event *event);
private:
    Sprite * sprite_flag_;
    Sprite * sprite_star_0;
    Sprite * sprite_star_1;
    Sprite * sprite_star_2;
    CC_SYNTHESIZE(int,level_,Level)
};

#endif
