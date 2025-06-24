#pragma once

class ItemManager;
class Monster;

class Dragon : public Monster {
public:
	Dragon(int level);

	Item* dropItem = ItemManager::Get().CreateItem("드래곤심장");
	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.5f; };
	float getMultiplyAtk() const override { return 1.5f; };
};