#pragma once

#include <string>
#include <vector>

class Monster;

class Slime : public Monster {
public:
	Slime(int level);

	Item* dropItem;

	std::string rollRandomItem() {
		std::vector<std::string> possibleItems = { "끈적한점액", "슬라임핵" };
		return possibleItems[getRandomInRange(0, possibleItems.size())];
	}

	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};