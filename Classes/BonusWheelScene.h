#pragma once

#ifndef __BONUSWHEEL_SCENE_H__
#define __BONUSWHEEL_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class BonusWheel : public cocos2d::Scene
{
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;

    cocos2d::Sprite* _wheelSprite;
    const int _wheelSectorCount = 8;
    const float _symbolRadius = 215.0f;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void playWheelSpinButtonCallback(cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheel);

private:

    void setupWheel();

    void populateWheel();

    void setupWheelSpinButton();
};

#endif // __BONUSWHEEL_SCENE_H__