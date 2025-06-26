#pragma once

#include <string>
#include <vector>

class Monster;

class Orc : public Monster {
public:
	Orc(int level);

	Item* dropItem;

	std::string rollRandomItem() {
		std::vector<std::string> possibleItems = { "상처난오크등가죽", "오크등가죽", "오크힘줄", "오크족전투휘장", "오크의어금니" };
		return possibleItems[getRandomInRange(0, possibleItems.size())];
	}

	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};