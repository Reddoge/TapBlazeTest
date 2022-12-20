#pragma once

#ifndef __BONUSWHEEL_SCENE_H__
#define __BONUSWHEEL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Wheel.h"

class BonusWheel : public cocos2d::Scene
{
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;

    cocos2d::Sprite* _wheelSprite;
    const float _symbolRadius = 215.0f;

    ui::Button* _button;
    std::unique_ptr<Wheel> _wheel;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void playWheelSpinButtonCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType test);

    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheel);

private:

    void SetupWheelSpinButton();

    void TestWheelSector(int sectorNumber);

    void EmulateSpins(int spinCount);
};

#endif // __BONUSWHEEL_SCENE_H__