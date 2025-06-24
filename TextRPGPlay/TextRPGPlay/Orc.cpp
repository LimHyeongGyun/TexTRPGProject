#include "Monster.h"
#include "Orc.h"
#include <vector>

Orc::Orc(int level) {
	name = "Orc";
	alive = true;

	int baseMinHp = level * 20;
	int baseMaxHp = level * 30;

	int baseMinAtk = level * 5;
	int baseMaxAtk = level * 10;

	health = getRandomInRange(baseMinHp, baseMaxHp);
	attack = getRandomInRange(baseMinAtk, baseMaxAtk);

	expDrop = 50;
	goldDrop = getRandomInRange(10, 20);

	ItemDrop();
}