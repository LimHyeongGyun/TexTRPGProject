#pragma once

#include "Monster.h"

class Troll : public Monster {
public:
	Troll(int level);

	Item* dropItem = ItemManager::GetInstance().CreateItem("고블린이빨");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};