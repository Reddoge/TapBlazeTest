#pragma once

#ifndef __BONUSWHEEL_SCENE_H__
#define __BONUSWHEEL_SCENE_H__

#include "cocos2d.h"

class BonusWheel : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void playOnSpinCallback(cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheel);
};

#endif // __BONUSWHEEL_SCENE_H__