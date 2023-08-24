#include "SlotMenuSprite.h"
#include "../Layer/GameLayer.h"
SlotMenuSprite::SlotMenuSprite()
{

}

SlotMenuSprite::~SlotMenuSprite()
{

}

bool SlotMenuSprite::initWithNum(int num)
{
    if(!Sprite::init()){
        return  false;
    }
   setNum(num);
   sprite_saveslot_ = Sprite::createWithSpriteFrameName("mainmenu_saveslot_0001.png");
   addChild(sprite_saveslot_);
//   menu_item_sprite_saveslot_delete_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_delete_0001.png"),
//                                                             Sprite::createWithSpriteFrameName("mainmenu_saveslot_delete_0002.png"),
//                                                             CC_CALLBACK_1(SlotMenuSprite::touchSavelotDelete,this));
//   menu_item_sprite_saveslot_delete_->setPosition(Point(sprite_saveslot_->getContentSize().width/2 - 20,sprite_saveslot_->getContentSize().height/2 - 20));
//   auto menu = Menu::create(menu_item_sprite_saveslot_delete_,nullptr);
//   menu->setPosition(Vec2::ZERO);
//   addChild(menu);

//   label_hint_ = Label::createWithTTF("DELETE SLOT?","Comic_Book.ttf",32,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
//   label_hint_->setColor(Color3B(219,205,139));
//   label_hint_->setPosition(Point(sprite_saveslot_->getContentSize().width/2,sprite_saveslot_->getContentSize().height/3*2));

//   menu_item_sprite_confirm_delete_ = MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png"),
//                                                             Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0001.png"),
//                                                             CC_CALLBACK_1(SlotMenuSprite::touchConformDelete,this));

//   menu_item_sprite_confirm_delete_->setPosition(Point(sprite_saveslot_->getContentSize().width/4,sprite_saveslot_->getContentSize().height/3));

//   menu_item_sprite_cancel_delete_ =  MenuItemSprite::create(Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png"),
//                                                             Sprite::createWithSpriteFrameName("mainmenu_saveslot_confirmdelete_0002.png"),
//                                                             CC_CALLBACK_1(SlotMenuSprite::touchConformDelete,this));
//   menu_item_sprite_cancel_delete_->setPosition(Point(sprite_saveslot_->getContentSize().width/4*3,sprite_saveslot_->getContentSize().height/3));

//   auto delete_menu = Menu::create(menu_item_sprite_confirm_delete_,menu_item_sprite_cancel_delete_,NULL);
//   delete_menu->setPosition(Vec2::ZERO);
//   auto confirm = Node::create();
//   confirm->addChild(label_hint_);
//   confirm->addChild(delete_menu);
//   confirm->setVisible(false);
   //sprite_saveslot_->addChild(confirm);

   if(UserDefault::getInstance()->getIntegerForKey(StringUtils::format("Slot%d",getNum()).c_str(),0) == 0){
        createNewGame();
     //   menu_item_sprite_saveslot_delete_->setVisible(false);
   }
   initEvent();
   return true;
}

void SlotMenuSprite::touchSavelotDelete(Ref *pSender)
{
    CCLOG("SlotMenuSprite::touchSavelotDelete");
}

void SlotMenuSprite::touchConformDelete(Ref *pSender)
{
     CCLOG("SlotMenuSprite::touchConformDelete");
}

void SlotMenuSprite::touchCancelDelete(Ref *pSender)
{
    CCLOG("SlotMenuSprite::touchCancelDelete");
}

bool SlotMenuSprite::touchBeganSaveslot(Touch *touch, Event *event)
{

    auto sprite = static_cast<Sprite*>(event->getCurrentTarget());
    Point localtoinInNode = sprite->convertTouchToNodeSpace(touch);
    Rect rect = Rect(0,0,sprite->getContentSize().width,sprite->getContentSize().height);
    if(rect.containsPoint(localtoinInNode)){
        sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("mainmenu_saveslot_0002.png"));
        CCLOG("SlotMenuSprite::touchBeganSaveslot");
        return  true;
    }
    return  false;
}

bool SlotMenuSprite::touchEndedSaveslot(Touch *touch, Event *event)
{
    // 跳转到游戏界面
    Director::getInstance()->replaceScene(GameLayer::createScene());
    return  false;
}

void SlotMenuSprite::createNewGame()
{
    auto label = Label::createWithTTF("new game","Comic_Book.ttf",42,Size::ZERO,TextHAlignment::LEFT,TextVAlignment::TOP);
    label->setColor(Color3B(219,205,139));
    label->setPosition(Point(sprite_saveslot_->getContentSize().width/2,sprite_saveslot_->getContentSize().height/2));
    sprite_saveslot_->addChild(label);
}

void SlotMenuSprite::initEvent()
{
    auto saveslot_listener = EventListenerTouchOneByOne::create();
    saveslot_listener->onTouchBegan = CC_CALLBACK_2(SlotMenuSprite::touchBeganSaveslot,this);
    saveslot_listener->onTouchEnded = CC_CALLBACK_2(SlotMenuSprite::touchEndedSaveslot,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(saveslot_listener,sprite_saveslot_);
}

SlotMenuSprite *SlotMenuSprite::createMenu(int num)
{
    auto slotMenu = new SlotMenuSprite();
    // 创建存储按钮
    if(slotMenu && slotMenu->initWithNum(num)){
        slotMenu->autorelease();
        return slotMenu;
    }
    CC_SAFE_DELETE(slotMenu);
    return nullptr;
}
