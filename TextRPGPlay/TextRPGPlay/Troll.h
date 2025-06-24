#pragma once

class ItemManager;
class Monster;

class Troll : public Monster {
public:
	Troll(int level);

	Item* dropItem = ItemManager::Get().CreateItem("고블린이빨");

	Item* getPossibleDrops() const override {
		return dropItem;
	}
};