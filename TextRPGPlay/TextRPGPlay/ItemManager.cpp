#include "ItemManager.h"

ItemManager& ItemManager::GetInstance() {
    static ItemManager instance; // 프로그램 시작 시 한번만 생성됨
    return instance;
}

ItemManager::ItemManager() {
    // === 게임에 등장하는 모든 아이템의 원본을 여기서 생성하고 등록 ===
    prototypes["힐링포션"] = std::make_unique<Potion>("힐링 포션", 50, 20);
    prototypes["롱소드"] = std::make_unique<Weapon>("롱소드", 150, 10);
    prototypes["가죽갑옷"] = std::make_unique<Armor>("가죽 갑옷", 100, 20);
    prototypes["철갑옷"] = std::make_unique<Armor>("철갑옷", 200, 50);

}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const std::string& name) {
    auto it = prototypes.find(name);
    if (it != prototypes.end()) {
        // 원본을 찾았으면, Clone()을 호출하여 복제품을 만들어 반환
        return it->second->Clone();
    }
    return nullptr; // 해당하는 이름의 아이템이 없으면 nullptr 반환
}