#include "Monster.h"
#include "Orc.h"
#include "ItemManager.h"
#include <vector>

Orc::Orc(int level) {
	name = "Orc";
	dropItem = ItemManager::Get().CreateItem("오크족전투휘장");
	alive = true;

	int baseMinHp = level * 20;
	int baseMaxHp = level * 30;

	int baseMinAtk = level * 5;
	int baseMaxAtk = level * 10;

	health = getRandomInRange(baseMinHp, baseMaxHp) * getMultiplyHp();
	attack = getRandomInRange(baseMinAtk, baseMaxAtk) * getMultiplyAtk();

	expDrop = 50;
	goldDrop = getRandomInRange(10, 20);

	ItemDrop();
}