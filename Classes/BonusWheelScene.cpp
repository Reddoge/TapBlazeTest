#include "BonusWheelScene.h"
#include "DropTable.h"
#include <cmath>
#include <functional>

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

    _wheel = std::make_unique<Wheel>(this);

    EmulateSpins(1000);

    SetupWheelSpinButton();

    return true;
}

void BonusWheel::SetupWheelSpinButton()
{
    //Setup Button position
    float buttonX = _origin.x + (_visibleSize.width * 0.5f);
    float buttonY = _origin.y + (_visibleSize.height / 8);

    auto label = Label::createWithTTF("PlayOn", "fonts/Marker Felt.ttf", 68);

    _button = ui::Button::create("spin_button.png", "", "");
    _button->setTitleLabel(label);
    _button->setPosition(Vec2(buttonX, buttonY));
    _button->setScale(0.8f);
    _button->addTouchEventListener(CC_CALLBACK_2(BonusWheel::playWheelSpinButtonCallback, this));
    this->addChild(_button);
}

void BonusWheel::playWheelSpinButtonCallback(cocos2d::Ref* sender, cocos2d::ui::Widget::TouchEventType type)
{
    if (type != cocos2d::ui::Widget::TouchEventType::ENDED)
        return;

    _button->setEnabled(false);
    _button->setTouchEnabled(false);
    _button->runAction(EaseIn::create(ScaleTo::create(0.5f, 0), 1));

    _wheel->SpinWheel();
}

void BonusWheel::TestWheelSector(int selector)
{
    _wheel->SpinWheel(selector);
}

void BonusWheel::EmulateSpins(int spinCount)
{
    auto dropTable = _wheel->GetDropTable();
    auto dropTableItems = dropTable->GetDropTableItems();

    std::map<DropTableItem*, int> dropTableMap;

    for (size_t i = 0; i < dropTableItems.size(); i++)
    {
        dropTableMap.insert(std::make_pair(dropTableItems[i], 0));
    }

    for (size_t i = 0; i < spinCount; i++)
    {
        auto dropTableItem = dropTable->RollTable();
        
        auto iter = dropTableMap.find(dropTableItem);
        if (iter != dropTableMap.end())
        {
            iter->second += 1;
        }
    }

    for (auto const& itemPair : dropTableMap)
    {
        auto tableItem = itemPair.first;

        CCLOG("Item: %s Quantity: %d Drop Weight: %d Number of Rolls: %d", tableItem->GetName().c_str(), tableItem->GetQuantity(), tableItem->GetDropChance(), itemPair.second);
    }
}
