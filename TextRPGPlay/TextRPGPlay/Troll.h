#pragma once

#include <string>
#include <vector>

class Monster;

class Troll : public Monster {
public:
	Troll(int level);

	Item* dropItem;

	std::string rollRandomItem() {
		std::vector<std::string> possibleItems = { "트롤의변이된손톱", "재생촉매이끼", "굳어버린트롤의피", "상처난트롤가죽", "트롤의가죽", "트롤의재생혈액"};
		return possibleItems[getRandomInRange(0, possibleItems.size())];
	}

	Item* getPossibleDrops() const override {
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};