#include "Monster.h"

string Monster::getName() const {
	return name;
}

int Monster::getHealth() const {
	return health;
}

int Monster::Attack() const {
	return attack;
}

void Monster::takeDamage(int damage) {
	health -= damage;
	if (health < 0) {
		health = 0;
		alive = false;
	}
}

int Monster::getExpDrop() const {
	return alive ? 0 : expDrop;
}

int Monster::getGoldDrop() const {
	return alive ? 0 : goldDrop;
}

bool Monster::IsAlive() {
	return alive;
}

void Monster::rollItemDrop() {
	const auto& items = getPossibleDrops();
	int idx = getRandomInRange(0, items.size() - 1);
	itemDrop = items[idx];
}

ItemType Monster::getItemDrop() const {
	return itemDrop;
}

string Monster::getItemDropName() const {
	return getItemName(itemDrop);
}
