#pragma once

using namespace std;

class Item;

class Character {
private:
	static Character* charInstance;

	string name; //플레이어 이름
	int level = 1; //레벨
	int maxLevel = 10;
	int health = 0; //현재 체력
	int maxHealth = 0; //최대 체력
	int attack = 0; //공격력
	int experience = 0; //경험치
	int needExperience = 100;
	int gold = 0; //소지 골드

	Item* equipWeapon;
	Item* equipArmor;

	void UpgradeStatus(); //레벨업 했을 때 스탯 업그레이드
	void LevelUp(); //레벨업

public:
	Character();
	static Character* Get(string name = " "); //싱글턴 인스턴스

	//플레이어 정보
	void DisplayStatus() const; //플레이어의 현재 스탯 확인
	string GetName() const; //플레이어 이름

	//전투 관련
	int Attack();
	void TakeDamage(int damage); //피격시
	void RecoveryHP(int health); //체력 회복
	void GetExperience(int experience); //경험치 획득 -> 몬스터 처치시 몬스터의 사망로직에서 호출하여 사용
	void GetItem(Item* item, int num);
	void Die();

	//아이템 관리
	void UseItem(int index); //아이템 사용
	Item* GetEquipWeapon(); //현재 장착 무기 반환
	Item* GetEquipArmor(); //현재 장착 방어구 반환
	void SetEquipWeapon(Item* weapon); //무기 장착
	void SetEquipArmor(Item* armor); //방어구 장착
	void EquipStatus(int getAttack, int getHealth); //장비 장착시 스탯 변환
	void UnEquipStatus(int getAttack, int getHealth); //장비 해제시 스탯 변환

	//골드 관련
	void GetGold(int getGold);
	void ConsumeGold(int consumeGold);
	void VisitShop(); //Shop과 상호작용

	~Character();
};