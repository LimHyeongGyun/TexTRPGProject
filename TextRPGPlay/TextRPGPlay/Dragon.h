#pragma once

#include <string>
#include <vector>

class Monster;

class Dragon : public Monster {
public:
	Dragon(int level);

	Item* dropItem;

	std::string rollRandomItem() {
		std::vector<std::string> possibleItems = { "드래곤의발톱", "드래곤심장", "드래곤비늘"};
		return possibleItems[getRandomInRange(0, possibleItems.size())];
	}

	Item* getPossibleDrops() const override{
		return dropItem;
	}

	float getMultiplyHp() const override { return 1.0f; };
	float getMultiplyAtk() const override { return 1.0f; };
};