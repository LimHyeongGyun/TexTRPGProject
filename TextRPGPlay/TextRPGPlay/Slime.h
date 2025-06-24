#pragma once

class ItemManager;
class Monster;

class Slime : public Monster {
public:
	Slime(int level);

	Item* dropItem = ItemManager::Get().CreateItem("끈적한점액");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};