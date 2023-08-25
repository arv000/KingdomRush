#ifndef _SPRITE_MAP_FLAG_SPRITE_H_
#define _SPRITE_SLOT_MENU_SPRITE_H_

#include "cocos2d.h"
USING_NS_CC;

class RoadSprite : public Sprite {

public:
    RoadSprite();
    ~RoadSprite();
    virtual bool init();

    CREATE_FUNC(RoadSprite)
        // 初始化路的动画效果
        void initRoadAnimation();
        void runActionRoadAnimation(int num);
        Vector<Sprite*> vector_road_;
        Vector<Animation*> vector_animation_road_;

};

#endif
