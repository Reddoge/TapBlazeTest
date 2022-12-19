#pragma once

#include <string>

class DropTableItem
{
	int _sector;

	std::string _name;

	int _quantity;

	int _dropWeight;

	/// <summary>
	/// This is used for the filename of the item, the file format needs to be included
	/// </summary>
	std::string _imageFileName;

	std::string _displayText;

public:

	DropTableItem(int sector, std::string name, int quantity, int dropWeight, std::string imageFileName);

	DropTableItem(int sector, std::string name, int quantity, int dropWeight, std::string imageFileName, std::string displayTextOverride);

	int GetSector() { return _sector; }

	std::string GetName() { return _name; }

	int GetQuantity() { return _quantity; }

	int GetDropChance() { return _dropWeight; }

	std::string GetFileName() { return _imageFileName; }

	std::string GetDisplayText() { return _displayText; }


	~DropTableItem();
};