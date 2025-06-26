#pragma once

#include <string>
#include <random>

class Item;

inline int getRandomInRange(int min, int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dist(min, max);

	return dist(gen);
}

class Monster {
protected:
	std::string name;
	int health = 0;
	int attack = 0;

	int expDrop = 0;
	int goldDrop = 0;

	bool alive = false;

public:
	std::string getName() const;				// 몬스터 이름
	int getHealth() const;						// 몬스터 체력
	int Attack() const;							// 몬스터 공격력
	void takeDamage(int damage);				// 몬스터가 받는 피해 (인수: 캐릭터의 대미지)

	virtual Item* getPossibleDrops() const = 0;
	virtual Item* ItemDrop();

	int getExpDrop() const;						// 경험치 드랍
	int getGoldDrop() const;					// 골드 드랍

	virtual bool IsAlive();						// 몬스터 사망 여부

	virtual float getMultiplyHp() const = 0;	// 체력 계수
	virtual float getMultiplyAtk() const = 0;	// 공격력 계수



	virtual ~Monster() {};
};