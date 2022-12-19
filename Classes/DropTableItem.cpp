#include "DropTableItem.h"

DropTableItem::DropTableItem(int sector, std::string name, int quantity, int dropWeight, std::string imageFileName)
{
	_sector = sector;
	_name = name;
	_quantity = quantity;
	_dropWeight = dropWeight;
	_imageFileName = imageFileName;
	_displayText = "x " + name;
}

DropTableItem::DropTableItem(int sector, std::string name, int quantity, int dropWeight, std::string imageFileName, std::string displayTextOverride)
{
	_sector = sector;
	_name = name;
	_quantity = quantity;
	_dropWeight = dropWeight;
	_imageFileName = imageFileName;
	_displayText = displayTextOverride;
}

DropTableItem::~DropTableItem()
{
}
