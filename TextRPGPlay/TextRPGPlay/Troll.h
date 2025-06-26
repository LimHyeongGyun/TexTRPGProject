#pragma once

class Monster;

class Troll : public Monster {
public:
	Troll(int level);

	Item* dropItem;
	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};