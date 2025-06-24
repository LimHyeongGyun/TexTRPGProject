#pragma once

#include "Monster.h"

class Goblin : public Monster {
public:
	Goblin(int level);

	Item* dropItem = ItemManager::Get().CreateItem("고블린이빨");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};