#include "ItemManager.h"
using namespace std;

ItemManager& ItemManager::Get() {
    static ItemManager instance; // ��ü ��ü�� static����
    return instance;
}

ItemManager::ItemManager() {
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Expendables, 50, 0, 0, 50);
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Expendables, 120, 0, 0, 100);
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Expendables, 250, 0, 0, 200);

    // --- ���� ����  ---
    Itemdb["������������"] = make_unique<Item>("���� ���� ����", ItemType::Expendables, 80, 0, 0, 80); // ������ ����
    Itemdb["Ʈ����������"] = make_unique<Item>("Ʈ�� �� ��� ���", ItemType::Expendables, 600, 0, 0, 400); // ��ġ�� �°� ���� ����
    Itemdb["��ȭ��������"] = make_unique<Item>("��ȭ�� ��� ���", ItemType::Expendables, 450, 0, 0, 280);
    Itemdb["�������"] = make_unique<Item>("����� ���", ItemType::Expendables, 2000, 0, 0, 1200); // ���� ��޿� �°� ���� �� ���� ����


    // =================================================================================
    // 2. ��� ������ (Weapons & Armors)
    // =================================================================================

    // --- �⺻ ���� ��� (������ ������ ����) ---
    Itemdb["�����ռҵ�"] = make_unique<Item>("���� �ռҵ�", ItemType::Weapon, 50, 25, 0, 0);
    Itemdb["���װ���"] = make_unique<Item>("���� ����", ItemType::Armor, 50, 0, 30, 0);
    Itemdb["��伮�ռҵ�"] = make_unique<Item>("��伮 �ռҵ�", ItemType::Weapon, 150, 60, 0, 0); // ���� ����ȭ
    Itemdb["�罽����"] = make_unique<Item>("�罽 ����", ItemType::Armor, 180, 0, 70, 0);
    Itemdb["ö�ռҵ�"] = make_unique<Item>("ö �ռҵ�", ItemType::Weapon, 280, 100, 0, 0);
    Itemdb["ö����"] = make_unique<Item>("ö ����", ItemType::Armor, 280, 0, 100, 0);


    // --- ���� ��� (�ܰ躰�� ���� �� ���� ������) ---

    // -- �ʱ� ���� ��Ʈ (���/������ ���) --
    Itemdb["�����ϴܰ�"] = make_unique<Item>("��� ��� �ܰ�", ItemType::Weapon, 90, 45, 0, 0);

    //�������� ����� �ִ� ����
    Itemdb["�����Ⱙ��"] = make_unique<Item>("������ ����", ItemType::Armor, 220, 0, 90, 0);

    // -- �߱� ���� ��Ʈ 1 (��ũ ���) --
    Itemdb["��ũ��ݴϵ���"] = make_unique<Item>("��ũ ��ݴ� ����", ItemType::Weapon, 350, 115, 0, 0); // ö �ռҵ庸�� Ȯ���� ������ ����
    Itemdb["��ũ���װ���"] = make_unique<Item>("��ũ ���� ����", ItemType::Armor, 350, 0, 115, 0); // ö���ʺ��� Ȯ���� ������ ����

    // -- �߱� ���� ��Ʈ 2 (Ʈ�� ���) --
    Itemdb["Ʈ�ѻ�������"] = make_unique<Item>("Ʈ�ѻ� ������", ItemType::Weapon, 500, 140, 0, 0);
    Itemdb["Ʈ�Ѱ��װ���"] = make_unique<Item>("Ʈ�Ѱ��� ����", ItemType::Armor, 500, 0, 140, 0);

    // -- ��� ���� ��Ʈ (���� - ���� ������ �޿�� ���� �ű� �߰�) --
    Itemdb["�����ǰ�"] = make_unique<Item>("������ ��", ItemType::Weapon, 1200, 230, 0, 0);
    Itemdb["��������"] = make_unique<Item>("���� ����", ItemType::Armor, 1200, 0, 230, 0);

    // -- �ֻ�� ���� ��Ʈ (�� ���) --
    Itemdb["������â"] = make_unique<Item>("������ â", ItemType::Weapon, 3500, 350, 0, 0);
    Itemdb["�����ǰ���"] = make_unique<Item>("������ ����", ItemType::Armor, 3500, 0, 350, 0);


    // =================================================================================
    // 3. ��� ������ (Materials) - ���ݸ� ���� ����
    // =================================================================================
    //������
    Itemdb["����������"] = make_unique<Item>("������ ����", ItemType::Other, 20, 0, 0, 0);
    Itemdb["��������"] = make_unique<Item>("������ ��", ItemType::Other, 50, 0, 0, 0);

    //���
    Itemdb["�����ָӴ�"] = make_unique<Item>("���� �ָӴ�", ItemType::Other, 10, 0, 0, 0);
    Itemdb["����̻�"] = make_unique<Item>("��� �̻�", ItemType::Other, 30, 0, 0, 0);
    Itemdb["����ǱͰ���"] = make_unique<Item>("����� �Ͱ���", ItemType::Other, 45, 0, 0, 0);
    Itemdb["��ģ��������"] = make_unique<Item>("��ģ ���� ����", ItemType::Other, 35, 0, 0, 0);

    //��ũ
    Itemdb["��ũ����"] = make_unique<Item>("��ũ ����", ItemType::Other, 40, 0, 0, 0);
    Itemdb["��ó����ũ���"] = make_unique<Item>("��ó �� ��ũ ���", ItemType::Other, 80, 0, 0, 0);
    Itemdb["��ũ����������"] = make_unique<Item>("��ũ�� ���� ����", ItemType::Other, 100, 0, 0, 0);
    Itemdb["��ũ�Ǿ�ݴ�"] = make_unique<Item>("��ũ�� ��ݴ�", ItemType::Other, 120, 0, 0, 0);
    Itemdb["��ũ���"] = make_unique<Item>("��ũ ���", ItemType::Other, 180, 0, 0, 0);


    //Ʈ��
    Itemdb["����˸��̳�"] = make_unique<Item>("��� �˸� �̳�", ItemType::Other, 500, 0, 0, 0);
    Itemdb["�������Ʈ������"] = make_unique<Item>("������� Ʈ���� ��", ItemType::Other, 150, 0, 0, 0);
    Itemdb["��ó��Ʈ�Ѱ���"] = make_unique<Item>("��ó �� Ʈ�� ����", ItemType::Other, 150, 0, 0, 0);
    Itemdb["Ʈ���ǰ���"] = make_unique<Item>("Ʈ���� ����", ItemType::Other, 200, 0, 0, 0);
    Itemdb["Ʈ�����������"] = make_unique<Item>("Ʈ���� ��� ����", ItemType::Other, 350, 0, 0, 0);
    Itemdb["Ʈ���Ǻ��̵ȼ���"] = make_unique<Item>("Ʈ���� ���̵� ����", ItemType::Other, 180, 0, 0, 0);
    //�巡��
    Itemdb["�巡����"] = make_unique<Item>("�巡�� ���", ItemType::Other, 500, 0, 0, 0);
    Itemdb["�巡���ǹ���"] = make_unique<Item>("�巡���� ����", ItemType::Other, 750, 0, 0, 0);
    Itemdb["�巡�����"] = make_unique<Item>("�巡�� ����", ItemType::Other, 1500, 0, 0, 0);

    //��Ÿ ������
    Itemdb["��ȭ��"] = make_unique<Item>("��ȭ��", ItemType::Other, 50, 0, 0, 0);
}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const ::string& name) {
    auto it = Itemdb.find(name);
    if (it != Itemdb.end()) {
        // ������ ã������, Clone()�� ȣ���Ͽ� ����ǰ�� ����� ��ȯ
        return it->second->Clone();
    }
    return nullptr; // �ش��ϴ� �̸��� �������� ������ nullptr ��ȯ
}