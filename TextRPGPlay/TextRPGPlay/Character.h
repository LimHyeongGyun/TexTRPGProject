#pragma once

#include <vector>
#include <string>

class Item;

class Character {
private:
	static Character* charInstance;

	std::string name; //�÷��̾� �̸�
	int level = 1; //����
	int maxLevel = 10;
	int health = 0; //���� ü��
	int maxHealth = 0; //�ִ� ü��
	int attack = 0; //���ݷ�
	int experience = 0; //����ġ
	int needExperience = 100;
	int gold = 0; //���� ���

	Item* equipWeapon;
	Item* equipArmor;

	void UpgradeStatus(); //������ ���� �� ���� ���׷��̵�
	void LevelUp(); //������

public:
	Character();
	static Character* Get(std::string playerName = " "); //�̱��� �ν��Ͻ�

	//�÷��̾� ����
	void DisplayStatus() const; //�÷��̾��� ���� ���� Ȯ��
	std::string GetName() const; //�÷��̾� �̸�

	//���� ����
	int Attack() const;
	void TakeDamage(int damage); //�ǰݽ�
	void RecoveryHP(int health); //ü�� ȸ��
	void GetExperience(int experience); //����ġ ȹ�� -> ���� óġ�� ������ ����������� ȣ���Ͽ� ���
	void Die();

	//������ ����
	void GetItem(std::vector<Item*> item) const;
	void UseItem(int index) const; //�������� ������ ���
	Item* GetEquipWeapon() const; //���� ���� ���� ��ȯ
	Item* GetEquipArmor() const; //���� ���� �� ��ȯ
	void SetEquipWeapon(Item* weapon); //���� ����
	void SetEquipArmor(Item* armor); //�� ����
	void EquipStatus(int getAttack, int getHealth); //��� ������ ���� ��ȯ
	void UnEquipStatus(int getAttack, int getHealth); //��� ������ ���� ��ȯ

	//��� ����
	void BorrowGold(int getGold);
	void ConsumeGold(int consumeGold);
	void VisitShop(); //Shop�� ��ȣ�ۿ�

	~Character();
};