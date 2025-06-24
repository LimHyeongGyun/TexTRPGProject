#pragma once

#include "ItemManager.h"

inline int getRandomInRange(int min, int max);
class Monster;

class Dragon : public Monster {
public:
	Dragon(int level);
	Item* dropItem = ItemManager::GetInstance().CreateItem("드래곤심장");

	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.5f; };
	float getMultiplyAtk() const override { return 1.5f; };
};