#pragma once

class ItemManager;
class Monster;

class Orc : public Monster {
public:
	Orc(int level);

	Item* dropItem = ItemManager::Get().CreateItem("오크족전투휘장");
	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};