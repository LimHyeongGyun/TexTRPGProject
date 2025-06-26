#pragma once

#include <string>
#include <vector>

class Monster;

class Goblin : public Monster {
public:
	Goblin(int level);

	Item* dropItem;

	std::string rollRandomItem() {
		std::vector<std::string> possibleItems = { "낡은주머니", "고블린이빨", "거친가죽조각"};
		return possibleItems[getRandomInRange(0, possibleItems.size())];
	}

	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};