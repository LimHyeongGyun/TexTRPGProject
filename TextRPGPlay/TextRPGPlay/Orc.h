#pragma once

#include "Monster.h"

class Orc : public Monster {
public:
	Orc(int level);

	Item* dropItem = ItemManager::GetInstance().CreateItem("오크족전투휘장");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};