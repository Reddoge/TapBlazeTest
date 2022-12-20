#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class DropTable;
class DropTableItem;

class Wheel
{
	Scene* _scene;

	Sprite* _wheelSprite;
	Sprite* _wheelBorderSprite;
	Sprite* _greenArrowSprite;

	const float _symbolRadius = 215.0f;

	DropTable* _dropTable;

	DropTableItem* _winningItem;

public:

	Wheel(cocos2d::Scene* scene);

	void SetupWheel();

	void PopulateWheel();

	/// <summary>
	/// This uses a default value to determine whether or not to spin randomly or to the desired sector
	/// </summary>
	/// <param name="desiredSector"></param>
	void SpinWheel(int desiredSector = 0);

	void WheelSpinFinished(DropTableItem* winningItem);

	DropTable* GetDropTable() const { return _dropTable; };

	~Wheel();
};