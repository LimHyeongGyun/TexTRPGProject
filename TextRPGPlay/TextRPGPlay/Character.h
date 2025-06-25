#pragma once

#include <vector>
#include <string>

class Item;

class Character {
private:
	static Character* charInstance;
	Character(std::string playerName);

	std::string name; //�÷��̾� �̸�
	int level = 1; //����
	int maxLevel = 10;
	int baseHealth = 0; //�÷��̾� ��ü ü�� (��� �Ǵ� ������ ȿ���� ������)
	int health = 0; //���� ü��
	int maxHealth = 0; //�ִ� ü��
	int baseAttack = 0; //�÷��̾� ��ü ���ݷ� (��� �Ǵ� ������ ȿ���� ������)
	int attack = 0; //���ݷ�
	int experience = 0; //����ġ
	int needExperience = 100;
	int gold = 0; //���� ���

	Item* equipWeapon;
	Item* equipArmor;

	void LevelUpStatus(); //������ ���� �� ���� ���׷��̵�
	void LevelUp(); //������

public:
	Character(const Character&) = delete;
	Character& operator=(const Character&) = delete;
	static Character& Get(std::string playerName = " "); //�̱��� �ν��Ͻ�

	//�÷��̾� ����
	void DisplayStatus() const; //�÷��̾��� ���� ���� Ȯ��
	std::string GetName() const; //�÷��̾� �̸�
	int GetHealth() const; //�÷��̾� ü��
	int GetLevel() const; //�÷��̾� ����
	int GetGold() const;
	void UpadatePlayerStatus(); //��� �Ǵ� ���������� �÷��̾��� ������ ����Ǿ�� �� �� ȣ��

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

	//��� ����
	void BorrowGold(int getGold);
	void ConsumeGold(int consumeGold);
	void VisitShop(); //Shop�� ��ȣ�ۿ�

	~Character();
};