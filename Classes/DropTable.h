#pragma once

#include <vector>
#include "DropTableItem.h"

class DropTable
{
	std::vector<DropTableItem*> dropTable;

public:

	DropTable();

	std::vector<DropTableItem*> GetDropTableItems() const;

	DropTableItem* GetItem(int sector) const;

	DropTableItem* RollTable();

	~DropTable();
};