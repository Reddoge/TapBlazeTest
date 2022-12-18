#include "BonusWheelScene.h"

USING_NS_CC;

Scene* BonusWheel::createScene()
{
    return BonusWheel::create();
}

bool BonusWheel::init()
{
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto playOnButton = MenuItemImage::create(
        "spin_button.png",
        "spin_button.png",
        CC_CALLBACK_1(BonusWheel::playOnSpinCallback, this));

    float x = origin.x + (visibleSize.width / 2);
    float y = origin.y + (visibleSize.height / 6);
    playOnButton->setPosition(Vec2(x, y));

    auto menu = Menu::create(playOnButton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);



    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    this->addChild(label, 1);

    return true;
}

void BonusWheel::playOnSpinCallback(cocos2d::Ref* sender)
{
    CCLOG("Callback works");
}