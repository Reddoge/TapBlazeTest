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

    _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();

    setupWheel();
    setupWheelSpinButton();


    auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    label->setAnchorPoint(cocos2d::Vec2(0.0f, 0.0f));
    this->addChild(label, 1);

    return true;
}

void BonusWheel::setupWheel()
{
    //Setup Wheel position
    float wheelX = _origin.x + (_visibleSize.width / 2);
    float wheelY = _origin.y + (_visibleSize.height / 2) + 70.0f;

    auto wheelSprite = Sprite::create("wheel_sections_8.png");
    wheelSprite->setPosition(Vec2(wheelX, wheelY));

    auto wheelBorderSprite = Sprite::create("wheel_border.png");
    wheelBorderSprite->setAnchorPoint(Vec2(0.0, 0.0));

    //auto greenArrow = Sprite::create("wheel_arrow.png");
    //greenArrow->setAnchorPoint(Vec2(0.5f, 0.5f));
    //greenArrow->setPosition(Vec2(0.0f, wheelY));

    this->addChild(wheelSprite, 0);
    wheelSprite->addChild(wheelBorderSprite, 1);
    //wheelBorderSprite->addChild(greenArrow, 0);
}

void BonusWheel::setupWheelSpinButton()
{
    //Setup Button position
    float buttonX = _origin.x + (_visibleSize.width / 2);
    float buttonY = _origin.y + (_visibleSize.height / 8);

    auto label = Label::createWithTTF("PlayOn", "fonts/Marker Felt.ttf", 68);

    auto button = ui::Button::create("spin_button.png", "", "");
    button->setTitleLabel(label);
    button->setPosition(Vec2(buttonX, buttonY));
    button->setScale(0.8f);
    button->addTouchEventListener(CC_CALLBACK_1(BonusWheel::playWheelSpinButtonCallback, this));
    this->addChild(button);
}

void BonusWheel::playWheelSpinButtonCallback(cocos2d::Ref* sender)
{
    CCLOG("Callback works");
}