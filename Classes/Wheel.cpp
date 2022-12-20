#include "Wheel.h"
#include "DropTable.h"
#include "ui/CocosGUI.h"
#include <cmath>

Wheel::Wheel(Scene* scene) : _scene(scene)
{
    _dropTable = new DropTable();

    SetupWheel();
    PopulateWheel();
}

void Wheel::SetupWheel()
{
    auto _visibleSize = Director::getInstance()->getVisibleSize();
    auto _origin = Director::getInstance()->getVisibleOrigin();

    //Setup Wheel position
    float wheelX = _origin.x + (_visibleSize.width * 0.5f);
    float wheelY = _origin.y + (_visibleSize.height * 0.5f) + 60.0f;

    _wheelSprite = Sprite::create("wheel_sections_8.png");
    _wheelSprite->setPosition(Vec2(wheelX, wheelY));

    _wheelBorderSprite = Sprite::create("wheel_border.png");
    _wheelBorderSprite->setPosition(Vec2(wheelX, wheelY));

    //Note that the X position of the arrow is referring to wheelX
    float arrowY = wheelY + (_wheelBorderSprite->getContentSize().height / 2) - 30.0f;

    _greenArrowSprite = Sprite::create("wheel_arrow.png");
    _greenArrowSprite->setPosition(Vec2(wheelX, arrowY));

    //Didn't parent wheel border due to a wobble that would occur, its not sitting correctly on the sprite
    _scene->addChild(_wheelSprite, 0);
    _scene->addChild(_wheelBorderSprite, 1);
    _scene->addChild(_greenArrowSprite, 2);

    _wheelSprite->setCascadeOpacityEnabled(true);
}

void Wheel::PopulateWheel()
{
    Vec2 wheelCenter = Vec2(_wheelSprite->getContentSize().width * 0.5f, _wheelSprite->getContentSize().height * 0.5f);

    std::vector<DropTableItem*> dropTableItems = _dropTable->GetDropTableItems();
    int wheelSectorCount = dropTableItems.size();

    //Divide total distance around the outside of the circle by the amount of sectors we need
    float anglePerSector = (M_PI * 2.0f) / wheelSectorCount;

    for (size_t i = 0; i < wheelSectorCount; i++)
    {
        DropTableItem* dropTableItem = dropTableItems[i];

        //Offset rotation of placing the symbols on the wheel
        float angle = (i + 0.5) * anglePerSector;

        //Calculate location to place symbol
        Vec2 symbolPosition = Vec2(sin(angle) * _symbolRadius, cos(angle) * _symbolRadius);

        //Offset symbol by the center of the wheel
        symbolPosition += wheelCenter;

        auto symbol = Sprite::create(dropTableItem->GetFileName());
        symbol->setPosition(symbolPosition);
        symbol->setRotation((i + 0.5) * (360 / wheelSectorCount));

        auto symbolLabel = Label::createWithTTF(dropTableItem->GetDisplayText(), "fonts/Marker Felt.ttf", 20);
        symbolLabel->enableOutline(Color4B(188, 74, 60, 255), 2);
        symbolLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
        symbolLabel->setPosition(Vec2(0.0f, -10.0f));

        _wheelSprite->addChild(symbol, 5);
        symbol->addChild(symbolLabel, 6);

        symbol->setCascadeOpacityEnabled(true);
    }
}

void Wheel::SpinWheel(int desiredSector)
{
    int sectorNumber = desiredSector;

    if (sectorNumber <= 0)
    {
        _winningItem = _dropTable->RollTable();
    }
    else
    {
        _winningItem = _dropTable->GetItem(sectorNumber);
    }

    if (!_winningItem)
    {
        CCLOG("Not going to spin, item was nullptr");
        return;
    }

    sectorNumber = _winningItem->GetSector();

    //Calculate desired offset
    int desiredItemAngleOffset = 720 - ((sectorNumber * 45) - 22.5f);

    cocos2d::Vector<cocos2d::FiniteTimeAction*> actionVector;
    actionVector.pushBack(RotateBy::create(0.5f, -5));
    actionVector.pushBack(EaseOut::create(RotateBy::create(4.0f, 1805), 0.5f));
    actionVector.pushBack(EaseIn::create(RotateBy::create(2.0f, desiredItemAngleOffset), 0.5f));

    auto callback = CallFunc::create([&]()
    {
        WheelSpinFinished(_winningItem);
    });

    actionVector.pushBack(callback);

    auto sequence = Sequence::create(actionVector);

    _wheelSprite->runAction(sequence);
}

void Wheel::WheelSpinFinished(DropTableItem* winningItem)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto winningItemImage = Sprite::create(winningItem->GetFileName());
    winningItemImage->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.5f));
    winningItemImage->setScale(0);
    _scene->addChild(winningItemImage, 10);

    auto symbolLabel = Label::createWithTTF(winningItem->GetDisplayText(), "fonts/Marker Felt.ttf", 20);
    symbolLabel->enableOutline(Color4B(188, 74, 60, 255), 2);
    symbolLabel->setAnchorPoint(Vec2(0.0f, 0.0f));
    symbolLabel->setPosition(Vec2(0.0f, -10.0f));
    winningItemImage->addChild(symbolLabel, 1);


    auto fadeWheelAction = CallFunc::create([&]()
    {
        _wheelSprite->runAction(FadeOut::create(1.0f));
        _wheelBorderSprite->runAction(FadeOut::create(1.0f));
        _greenArrowSprite->runAction(FadeOut::create(1.0f));
    });

    _scene->runAction(Sequence::create(
        DelayTime::create(1.2f),
        fadeWheelAction,
        NULL
    ));

    winningItemImage->runAction(Sequence::create(
        DelayTime::create(2.2f),
        EaseBounceOut::create(ScaleTo::create(1.0f, 1.0f)),
        NULL));
}

Wheel::~Wheel()
{
    delete _dropTable;
}