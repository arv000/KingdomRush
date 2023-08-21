#ifndef _SPRITE_SLOT_MENU_SPRITE_H_
#define _SPRITE_SLOT_MENU_SPRITE_H_

#include "cocos2d.h"
USING_NS_CC;

class SlotMenuSprite : public Sprite {

public:
    SlotMenuSprite();
    ~SlotMenuSprite();
    virtual bool initWithNum(int num);
    CREATE_FUNC(SlotMenuSprite)

        void touchSavelotDelete(Ref * pSender);
        void touchConformDelete(Ref *pSender);
        void touchCancelDelete(Ref *pSender);
        bool touchBeganSaveslot(Touch* touch,Event * event);
        bool touchEndedSaveslot(Touch* touch,Event * event);
        void createNewGame();
        void initEvent();
        static SlotMenuSprite *createMenu(int num);

private:
    Label *label_hint_;
    MenuItemSprite *menu_item_sprite_saveslot_delete_;
    Sprite *sprite_saveslot_;
    MenuItemSprite *menu_item_sprite_confirm_delete_;
    MenuItemSprite *menu_item_sprite_cancel_delete_;
    CC_SYNTHESIZE(int,num,Num)
};

#endif
