#include "ChooseDifficultyScene.h"
#include "../Layer/PlayerStateMenuLayer.h"
#include "GameScene.h"
USING_NS_CC;


Scene* ChooseDifficultyScene::createSceneWithLevel(int level)
{
    auto scene = Scene::create();
    auto layer = ChooseDifficultyScene::create();
    layer->initWithLevel(level);
    scene->addChild(layer);
    return scene;
}

void ChooseDifficultyScene::initWithLevel(int level)
{
    ValueVector txt_description = FileUtils::getInstance()->getValueVectorFromFile(StringUtils::format("xml/level%d_description.xml",level));
    setLevel(level);
    int i = 0;
    for(auto& e:txt_description){
        auto txt_map = txt_description.at(i).asValueMap();
        int id_init = txt_map.at("id").asInt();
        if(i == id_init){
            str_blue_top_ = txt_map.at("blueStrTop").asString();
            str_black_[0] = txt_map.at("blackStr1").asString();
            str_black_[1] = txt_map.at("blackStr2").asString();
            str_black_[2] = txt_map.at("blackStr3").asString();
            str_blue_[0] = txt_map.at("blueStr1").asString();
            str_blue_[1] = txt_map.at("blueStr2").asString();
            str_blue_[2] = txt_map.at("blueStr3").asString();
        }
        i++;
    }


    auto label1 = Label::createWithTTF(str_blue_top_,"fonts/Marker Felt.ttf",40);
    label1->setPosition(Point(visible_size_.width * 0.5,620));
    label1->setColor(Color3B(0,0,0));
    label1->setRotation(3.0f);
    label1->setAnchorPoint(Point(0,1));
    addChild(label1,1);

    label_blue_ = Label::createWithTTF(str_blue_[0],"fonts/Marker Felt.ttf",30);
    label_blue_->setPosition(Point(visible_size_.width * 0.5,570));
    label_blue_->setColor(Color3B(65,94,241));
    label_blue_->setRotation(3.0f);
    label_blue_->setAnchorPoint(Point(0,1));
    addChild(label_blue_,1);

    label_black_ = Label::createWithTTF(str_black_[0],"fonts/Marker Felt.ttf",21);
    label_black_->setPosition(Point(visible_size_.width * 0.5,525));
    label_black_->setColor(Color3B(0,0,0));
    label_black_->setRotation(3.0f);
    label_black_->setAnchorPoint(Point(0,1));
    addChild(label_black_,1);

    // 放大镜里面的东西。
    auto sprite_thumb = Sprite::createWithSpriteFrameName("thumb_stage2.png");
    sprite_thumb->setPosition(Point(260,400));
    addChild(sprite_thumb,1);

}


// on "init" you need to initialize your instance
bool ChooseDifficultyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    visible_size_ = Director::getInstance()->getVisibleSize();
    // 第一层背景,木板背景
    for (int i = 0; i< 4; i++) {
        for(int j = 0 ; j < 5 ;j ++){
            auto sprite = Sprite::createWithSpriteFrameName("encyclopedia_bgTile.png");
            sprite->setPosition(Point(i*320,j*160));
            sprite->setAnchorPoint(Point(0,0));
            addChild(sprite);
        }
    }
    // 第二层背景,纸张和地图
    auto sprite_bg2 = Sprite::createWithSpriteFrameName("LevelSelect_Bg.png");
    sprite_bg2->setPosition(Point(visible_size_.width/2,visible_size_.height/2));
    addChild(sprite_bg2,1);

    // 第三层背景放大镜
    auto sprite_loupe = Sprite::createWithSpriteFrameName("LevelSelect_loupe.png");
    sprite_loupe->setPosition(Point(visible_size_.width*0.21,390));
    addChild(sprite_loupe,2);

    // 关闭按钮
    auto sprite_close = MenuItemSprite::create(Sprite::createWithSpriteFrameName("LevelSelect_Back_0001.png"),
                                               Sprite::createWithSpriteFrameName("LevelSelect_Back_0002.png"),
                                               CC_CALLBACK_1(ChooseDifficultyScene::touchReturnMapSenec,this));
    Menu *menu_close = Menu::create(sprite_close,nullptr);
    sprite_close->setPosition(visible_size_.width*0.87,580);
    menu_close->setPosition(Vec2::ZERO);
    addChild(menu_close,2);

    // 进度战斗按钮
    auto sprite_start_mode = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_startMode_0001.png"),
                                                    Sprite::createWithSpriteFrameName("levelSelect_startMode_0002.png"),
                                                    CC_CALLBACK_1(ChooseDifficultyScene::touchPlayGame,this));

    Menu* menu_start_mode = Menu::create(sprite_start_mode,nullptr);
    sprite_start_mode->setPosition(Point(visible_size_.width*0.8,100));
    sprite_start_mode->setPosition(Vec2::ZERO);
    addChild(menu_start_mode,2);

    // 第一颗 小星星
    sprite_star1 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
    sprite_star1->setPosition(Point(170,580));
    sprite_star1->setRotation(-30.0f);
    addChild(sprite_star1,9);

    // 第一颗 小星星
    sprite_star2 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
    sprite_star2->setPosition(Point(220,600));
    sprite_star2->setRotation(-15.0f);
    addChild(sprite_star2,9);

    // 第一颗 小星星
    sprite_star3 = Sprite::createWithSpriteFrameName("levelSelect_badges_0002.png");
    sprite_star3->setPosition(Point(270,605));
    addChild(sprite_star3,9);

    // 盾牌
    sprite_star4 = Sprite::createWithSpriteFrameName("levelSelect_badges_0004.png");
    sprite_star4->setPosition(Point(320,600));
    sprite_star3->setRotation(15.0f);
    addChild(sprite_star4,9);

    // 拳头
    sprite_star5 = Sprite::createWithSpriteFrameName("levelSelect_badges_0006.png");
    sprite_star5->setPosition(Point(370,580));
    sprite_star5->setRotation(30.0f);
    addChild(sprite_star5,9);

    ///=============================按钮1===============================
    auto menu_item_normal1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"),
                                              Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"));
    auto menu_ite_select1 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0001.png"),
                                              Sprite::createWithSpriteFrameName("levelSelect_butModes_0005.png"));

    toggle_item1_ = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChooseDifficultyScene::touchStarMenu1,this)
                                               ,menu_item_normal1
                                               ,menu_ite_select1
                                               ,nullptr);
    toggle_item1_->setTag(1);
    toggle_item1_->setPosition(Point(visible_size_.width*0.12,20));
    toggle_item1_->setSelectedIndex(0);  // 初始化时设置0项为选中项
    toggle_item1_->setEnabled(true);
    ///=============================按钮2===============================
    auto menu_item_normal2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"),
                                                     Sprite::createWithSpriteFrameName("levelSelect_butModes_0006.png"));
    auto menu_ite_select2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png"),
                                                   Sprite::createWithSpriteFrameName("levelSelect_butModes_0002.png"));
    auto menu_ite_disable2 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),
                                                   Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));

     toggle_item2_ = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChooseDifficultyScene::touchStarMenu2,this)
                                                           ,menu_item_normal2
                                                           ,menu_ite_select2
                                                           ,menu_ite_disable2
                                                           ,nullptr);
    toggle_item2_->setPosition(Point(visible_size_.width*0.24,20));
    toggle_item2_->setSelectedIndex(2);  // 初始化时设置0项为选中项
    toggle_item2_->setEnabled(true);
    ///=============================按钮2===============================
    auto menu_item_normal3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"),
                                                     Sprite::createWithSpriteFrameName("levelSelect_butModes_0007.png"));
    auto menu_ite_select3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"),
                                                   Sprite::createWithSpriteFrameName("levelSelect_butModes_0003.png"));
    auto menu_ite_disable3 = MenuItemSprite::create(Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"),
                                                   Sprite::createWithSpriteFrameName("levelSelect_butModes_0004.png"));
    toggle_item3_ = MenuItemToggle::createWithCallback(CC_CALLBACK_1(ChooseDifficultyScene::touchStarMenu3,this)
                                                           ,menu_item_normal3
                                                           ,menu_ite_select3
                                                           ,menu_ite_disable3
                                                           ,nullptr);
    toggle_item3_->setPosition(Point(visible_size_.width*0.36,20));
    toggle_item3_->setSelectedIndex(2);  // 初始化时设置0项为选中项
    toggle_item3_->setEnabled(true);
    auto toggle_menu = Menu::create(toggle_item1_,toggle_item2_,toggle_item3_,nullptr);
    toggle_menu->setPosition(Point(0,0));
    addChild(toggle_menu,2);
    return true;

}

void ChooseDifficultyScene::touchStarMenu1(Ref *)
{
    CCLOG("ChooseDifficultyScene::touchStarMenu1 start");
    setDifficulty(0);
    toggle_item1_->runAction(MoveBy::create(0.1f,Point(0,20)));
    if(toggle_item2_->getSelectedIndex() ==0){
         toggle_item2_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    if(toggle_item3_->getSelectedIndex() ==0){
         toggle_item3_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    toggle_item1_->setEnabled(false);
    toggle_item1_->setSelectedIndex(0);
    toggle_item2_->setSelectedIndex(1);
    toggle_item2_->setEnabled(true);
    toggle_item3_->setSelectedIndex(1);
    toggle_item3_->setEnabled(true);

    label_blue_->setString(str_blue_[0]);
    label_black_->setString(str_black_[0]);
}

void ChooseDifficultyScene::touchStarMenu2(Ref *)
{
     CCLOG("ChooseDifficultyScene::touchStarMenu2 start");
    setDifficulty(1);

    toggle_item2_->runAction(MoveBy::create(0.1f,Point(0,20)));
    if(toggle_item1_->getSelectedIndex() ==0){
         toggle_item1_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    if(toggle_item3_->getSelectedIndex() ==0){
         toggle_item3_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    toggle_item2_->setEnabled(false);
    toggle_item2_->setSelectedIndex(0);
    toggle_item1_->setSelectedIndex(1);
    toggle_item1_->setEnabled(true);
    toggle_item3_->setSelectedIndex(1);
    toggle_item3_->setEnabled(true);

    label_blue_->setString(str_blue_[1]);
    label_black_->setString(str_black_[1]);
}

void ChooseDifficultyScene::touchStarMenu3(Ref *)
{
    CCLOG("ChooseDifficultyScene::touchStarMenu3 start");
    setDifficulty(2);
    toggle_item3_->runAction(MoveBy::create(0.1f,Point(0,20)));
    if(toggle_item1_->getSelectedIndex() ==0){
         toggle_item1_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    if(toggle_item2_->getSelectedIndex() ==0){
         toggle_item2_->runAction(MoveBy::create(0.1f,Point(0,-20)));
    }
    toggle_item3_->setEnabled(false);
    toggle_item3_->setSelectedIndex(0);
    toggle_item1_->setSelectedIndex(1);
    toggle_item1_->setEnabled(true);
    toggle_item2_->setSelectedIndex(1);
    toggle_item2_->setEnabled(true);

    label_blue_->setString(str_blue_[2]);
    label_black_->setString(str_black_[2]);
}

void ChooseDifficultyScene::touchReturnMapSenec(Ref *)
{
    Director::getInstance()->popScene();
}

void ChooseDifficultyScene::touchPlayGame(Ref *pSpender)
{
    Director::getInstance()->replaceScene(GameScene::createGameScene(getLevel(),getDifficulty()));
}
