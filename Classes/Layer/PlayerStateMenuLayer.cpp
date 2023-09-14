#include "PlayerStateMenuLayer.h"


bool PlayerStateMenuLayer::init()
{
    if( !Layer::init() ){
        return false;
    }
    win_size_ = Director::getInstance()->getWinSize();
    initSprite();
    initEvent();

    return true;
}

void PlayerStateMenuLayer::initSprite()
{
    // 显示 生命值,金币,怪物波数的背景
    sprite_state_ = Sprite::createWithSpriteFrameName("hud_background.png");
    sprite_state_->setAnchorPoint(Point(0,1));
    sprite_state_->setPosition(Point(20,win_size_.height - 20 + 100));
    addChild(sprite_state_);

    // 生命值
    label_life_ = Label::createWithTTF("0","fonts/arial.ttf",20);
    label_life_->setPosition(Point(sprite_state_->getContentSize().width*0.25,sprite_state_->getContentSize().height*0.75));
    sprite_state_->addChild(label_life_);

    // 金币值
    label_gold_ = Label::createWithTTF("0","fonts/arial.ttf",20);
    label_gold_->setPosition(Point(sprite_state_->getContentSize().width*0.75,sprite_state_->getContentSize().height*0.75));
    sprite_state_->addChild(label_gold_);

    // 当前怪物波数
    label_wave_ = Label::createWithTTF("0","fonts/arial.ttf",20);
    label_wave_->setPosition(Point(sprite_state_->getContentSize().width*0.5,sprite_state_->getContentSize().height*0.25));
    sprite_state_->addChild(label_wave_);

    // 暂停按钮
    sprite_pause_ = Sprite::createWithSpriteFrameName("hud_buttons_0001.png");
    sprite_pause_->setAnchorPoint(Point(1,1));
    sprite_pause_->setPosition(Point(win_size_.width -20,win_size_.height - 20 + 100));
    addChild(sprite_pause_);

//    // 拓展功能：雷石
    sprite_thunder_stone_ = Sprite::createWithSpriteFrameName("power_portrait_fireball_0001.png");
    sprite_thunder_stone_->setAnchorPoint(Point(0,0));
    sprite_thunder_stone_->setPosition(Point(10,-20));
    sprite_thunder_stone_->setName("inactive");
    addChild(sprite_thunder_stone_,1);

    // 拓展功能：伞兵
    sprite_paratrooper_ = Sprite::createWithSpriteFrameName("power_portrait_reinforcement_0001.png");
    sprite_paratrooper_->setAnchorPoint(Point(0,0));
    sprite_paratrooper_->setPosition(Point(120,-20));
    sprite_paratrooper_->setName("inactive");
    addChild(sprite_paratrooper_,1);


    // 拓展功能：锦囊
    sprite_pack_ = Sprite::createWithSpriteFrameName("power_portrait_backpack_0001.png");
    sprite_pack_->setAnchorPoint(Point(1,0));
    sprite_pack_->setPosition(Point(win_size_.width - 10,-20));
    sprite_pack_->setName("inactive");
    addChild(sprite_pack_,1);

    // 锦囊背景
    sprite_back_pack_ = Sprite::createWithSpriteFrameName("backPack_hover.png");
    sprite_back_pack_->setAnchorPoint(Point(1,0));
    sprite_back_pack_->setPosition(Point(win_size_.width - 60,30));
    sprite_back_pack_->setVisible(true);
    addChild(sprite_back_pack_,-1);

    for(int i = 1; i <=6 ; i ++){
            int num = 3;
            if(num > 0){
                stringForSkillFileName = StringUtils::format("backPack_icons_000%d.png",i);
            }else{
                stringForSkillFileName = StringUtils::format("backPack_icons_off_000%d.png",i+1);
            }
            sprite_backPack_icons_[i] = Sprite::createWithSpriteFrameName(stringForSkillFileName);
            sprite_backPack_icons_[i]->setAnchorPoint(Point(1,0));
            sprite_backPack_icons_[i]->setPosition(Point(640 - 85 * i,-20));

            sprite_backPack_icons_[i]->setTag(i);
            sprite_backPack_icons_[i]->setName(StringUtils::format("shop%d",i));
            sprite_back_pack_->addChild(sprite_backPack_icons_[i],0);

            auto numLeft = Label::createWithTTF(StringUtils::format("%d",num),"fonts/arial.ttf",20);
            numLeft->setPosition(Point(sprite_backPack_icons_[i]->getContentSize().width/4*3,sprite_backPack_icons_[i]->getContentSize().height/4));
            numLeft->setTag(101);
            sprite_backPack_icons_[i]->addChild(numLeft);
        }
    // 倒计时涂层
    timer_stone_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
    timer_stone_->setAnchorPoint(Point(0,0));
    timer_stone_->setReverseDirection(true);
    timer_stone_->setPosition(Point(10,-20));
    timer_stone_->setPercentage(50);
    addChild(timer_stone_,1,100);

    // 倒计时涂层
    timer_paratrooper_ = ProgressTimer::create(Sprite::createWithSpriteFrameName("power_loading.png"));
    timer_paratrooper_->setAnchorPoint(Point(0,0));
    timer_paratrooper_->setReverseDirection(true);
    timer_paratrooper_->setPosition(Point(120,-20));
    timer_paratrooper_->setPercentage(100);
    addChild(timer_paratrooper_,1,200);

}

void PlayerStateMenuLayer::initEvent()
{
    // 添加暂停 按钮的监听。
    auto sprite_pause_listener = EventListenerTouchOneByOne::create();
    sprite_pause_listener->onTouchBegan = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpirtePause,this);
    sprite_pause_listener->onTouchEnded = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchEnedSpirtePause,this);
    sprite_pause_listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sprite_pause_listener,sprite_pause_);

    // 添加雷石监听
    auto sprite_thunder_stone_listener = EventListenerTouchOneByOne::create();
    sprite_thunder_stone_listener->onTouchBegan = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpriteThunderStone,this);
    sprite_thunder_stone_listener->onTouchEnded = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchEnedSSpriteThunderStone,this);
    sprite_thunder_stone_listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sprite_thunder_stone_listener,sprite_thunder_stone_);

    // 添加伞兵监听
    auto sprite_paratrooper_listener = EventListenerTouchOneByOne::create();
    sprite_paratrooper_listener->onTouchBegan = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpriteParatrooper,this);
    sprite_paratrooper_listener->onTouchEnded = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpriteParatrooper,this);
    sprite_paratrooper_listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sprite_paratrooper_listener,sprite_paratrooper_);

    // 添加锦囊监听
    auto sprite_pack_listener = EventListenerTouchOneByOne::create();
    sprite_pack_listener->onTouchBegan = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpritePack,this);
    sprite_pack_listener->onTouchEnded = CC_CALLBACK_2(PlayerStateMenuLayer::onTouchBeganSpritePack,this);
    sprite_pack_listener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(sprite_pack_listener,sprite_pack_);
}

bool PlayerStateMenuLayer::onTouchBeganSpirtePause(Touch *touch, Event *event)
{
    return true;
}

void PlayerStateMenuLayer::onTouchEnedSpirtePause(Touch *touch, Event *event)
{

}

bool PlayerStateMenuLayer::onTouchBeganSpriteThunderStone(Touch *touch, Event *event)
{
     return false;
}

void PlayerStateMenuLayer::onTouchEnedSSpriteThunderStone(Touch *touch, Event *event)
{

}

bool PlayerStateMenuLayer::onTouchBeganSpriteParatrooper(Touch *touch, Event *event)
{
     return false;
}

void PlayerStateMenuLayer::onTouchEnedSSpriteParatrooper(Touch *touch, Event *event)
{

}

bool PlayerStateMenuLayer::onTouchBeganSpritePack(Touch *touch, Event *event)
{
    return false;
}

void PlayerStateMenuLayer::onTouchEnedSSpritePack(Touch *touch, Event *event)
{

}

void PlayerStateMenuLayer::onEnterTransitionDidFinish()
{
    sprite_state_->runAction(MoveBy::create(0.2f,Point(0,-100)));
}
