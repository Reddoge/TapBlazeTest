#include "BonusWheelScene.h"
#include <cmath>

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
    populateWheel();
    setupWheelSpinButton();

    return true;
}

void BonusWheel::setupWheel()
{
    //Setup Wheel position
    float wheelX = _origin.x + (_visibleSize.width / 2);
    float wheelY = _origin.y + (_visibleSize.height / 2) + 60.0f;

    _wheelSprite = Sprite::create("wheel_sections_8.png");
    _wheelSprite->setPosition(Vec2(wheelX, wheelY));

    auto wheelBorderSprite = Sprite::create("wheel_border.png");
    wheelBorderSprite->setPosition(Vec2(wheelX, wheelY));

    //Note that the X position of the arrow is referring to wheelX
    float arrowY = wheelY + (wheelBorderSprite->getContentSize().height / 2) - 30.0f;

    auto greenArrow = Sprite::create("wheel_arrow.png");
    greenArrow->setPosition(Vec2(wheelX, arrowY));

    //Didn't parent wheel border due to a wobble that would occur, its not sitting correctly on the sprite
    this->addChild(_wheelSprite, 0);
    this->addChild(wheelBorderSprite, 1);
    this->addChild(greenArrow, 2);
}

void BonusWheel::populateWheel()
{
    Vec2 wheelCenter = Vec2(_wheelSprite->getContentSize().width * 0.5f, _wheelSprite->getContentSize().height * 0.5f);

    //Divide total distance around the outside of the circle by the amount of sectors we need
    float anglePerSector = (M_PI * 2.0f) / _wheelSectorCount;

    for (size_t i = 0; i < _wheelSectorCount; i++)
    {
        //Offset rotation of placing the symbols on the wheel
        float angle = (i + 0.5) * anglePerSector;

        //Calculate location to place symbol
        Vec2 symbolPosition = Vec2(sin(angle) * _symbolRadius, cos(angle) * _symbolRadius);

        //Offset symbol by the center of the wheel
        symbolPosition += wheelCenter;

        auto symbol = Sprite::create("heart.png");
        symbol->setPosition(symbolPosition);
        symbol->setRotation((i + 0.5) * 45);

        auto symbolLabel = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 20);
        symbolLabel->enableOutline(Color4B(188, 74, 60, 255), 2);
        symbolLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
        symbolLabel->setPosition(Vec2(0.0f, -10.0f));
        
        _wheelSprite->addChild(symbol, 5);
        symbol->addChild(symbolLabel, 6);
    }
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
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actionVector;
    actionVector.pushBack(RotateBy::create(0.5f, -5));
    actionVector.pushBack(RotateBy::create(1.0f, 500));
    

    auto callback = CallFuncN::create([&](Node* node) {
        CCLOG("Callback works 2");
        });

    actionVector.pushBack(callback);
    
    auto sequence = Sequence::create(actionVector);

    _wheelSprite->runAction(sequence);

    CCLOG("Callback works");
}