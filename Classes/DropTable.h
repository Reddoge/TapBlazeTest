#pragma once

#include <vector>
#include "DropTableItem.h"

class DropTable
{
	std::vector<DropTableItem*> dropTable;

public:

	DropTable();

	void OverrideTable();

	std::vector<DropTableItem*> GetDropTableItems() const;

	DropTableItem* RollTable();

	~DropTable();
};