#include "DropTable.h"
#include "cocos2d.h"

DropTable::DropTable()
{
	dropTable = std::vector<DropTableItem*>();

	//Could move this to a file or API call
	dropTable.push_back(new DropTableItem(1, "Life", 30, 20, "heart.png", "30 min"));
	dropTable.push_back(new DropTableItem(2, "Brush", 3, 10, "brush.png"));
	dropTable.push_back(new DropTableItem(3, "Gems", 35, 10, "gem.png"));
	dropTable.push_back(new DropTableItem(4, "Hammer", 3, 10, "hammer.png"));
	dropTable.push_back(new DropTableItem(5, "Coins", 750, 5, "coin.png"));
	dropTable.push_back(new DropTableItem(6, "Brush", 1, 20, "brush.png"));
	dropTable.push_back(new DropTableItem(7, "Gems", 75, 5, "gem.png"));
	dropTable.push_back(new DropTableItem(8, "Hammer", 1, 20, "hammer.png"));
}

void DropTable::OverrideTable()
{

}

std::vector<DropTableItem*> DropTable::GetDropTableItems() const
{
	return dropTable;
}

DropTableItem* DropTable::RollTable()
{
	int totalDropChance = 0;

	for (auto &item : dropTable)
	{
		totalDropChance += item->GetDropChance();
	}

	//Generating Random number using total weight of all items
	int randomNumber = cocos2d::RandomHelper::random_int(0, totalDropChance);

	for (auto& item : dropTable)
	{
		//If the number is lower than the drop weight, we found our item
		if (randomNumber <= item->GetDropChance())
		{
			return item;
		}

		//Else, subtract from the random number to check the next item
		randomNumber -= item->GetDropChance();
	}

	CCLOG("DropTable::RollTable() code should not be reachable/n");
	return nullptr;
}

DropTable::~DropTable()
{
	for (size_t i = 0; i < dropTable.size(); i++)
	{
		delete dropTable[i];
	}

	dropTable.clear();
}