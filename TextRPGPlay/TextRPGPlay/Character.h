#pragma once

#include <vector>
#include <string>

class Item;

class Character {
private:
	static Character* charInstance;
	Character(std::string playerName);

	std::string name; //플레이어 이름
	int level = 1; //레벨
	int maxLevel = 10;
	int baseHealth = 0; //플레이어 자체 체력 (장비 또는 포션의 효과를 제외한)
	int health = 0; //현재 체력
	int maxHealth = 0; //최대 체력
	int baseAttack = 0; //플레이어 자체 공격력 (장비 또는 포션의 효과를 제외한)
	int attack = 0; //공격력
	int experience = 0; //경험치
	int needExperience = 100;
	int gold = 0; //소지 골드

	Item* equipWeapon;
	Item* equipArmor;

	void LevelUpStatus(); //레벨업 했을 때 스탯 업그레이드
	void LevelUp(); //레벨업

public:
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	static Character& Get(std::string playerName = " "); //싱글턴 인스턴스

	//플레이어 정보
	void DisplayStatus() const; //플레이어의 현재 스탯 확인
	std::string GetName() const; //플레이어 이름
	int GetHealth() const; //플레이어 체력
	int GetLevel() const; //플레이어 레벨
	int GetGold() const;
	void UpadatePlayerStatus(); //장비 또는 아이템으로 플레이어의 스탯이 변경되어야 할 때 호출

	//전투 관련
	int Attack() const;
	void TakeDamage(int damage); //피격시
	void RecoveryHP(int health); //체력 회복
	void GetExperience(int experience); //경험치 획득 -> 몬스터 처치시 몬스터의 사망로직에서 호출하여 사용
	void Die();

	//아이템 관리
	void GetItem(std::vector<Item*> item) const;
	void UseItem(int index) const; //전투에서 아이템 사용
	Item* GetEquipWeapon() const; //현재 장착 무기 반환
	Item* GetEquipArmor() const; //현재 장착 방어구 반환
	void SetEquipWeapon(Item* weapon); //무기 장착
	void SetEquipArmor(Item* armor); //방어구 장착

	//골드 관련
	void BorrowGold(int getGold);
	void ConsumeGold(int consumeGold);
	void VisitShop(); //Shop과 상호작용

	~Character();
};