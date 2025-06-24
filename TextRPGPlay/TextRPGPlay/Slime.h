#pragma once

#include "Monster.h"

class Slime : public Monster {
public:
	Slime(int level);

	Item* dropItem = ItemManager::GetInstance().CreateItem("끈적한점액");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};