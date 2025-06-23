#include "ItemManager.h"
using namespace std;

ItemManager& ItemManager::GetInstance() {
    static ItemManager instance; // 객체 자체를 static으로
    return instance;
}

ItemManager::ItemManager() {
    // === 게임에 등장하는 모든 아이템의 원본을 여기서 생성하고 등록 ===

    Itemdb["소형힐링포션"] = make_unique<Item>("소형 힐링 포션", ItemType::Potion,/*가격*/50, 0, 0, 50);
    Itemdb["중형힐링포션"] = make_unique<Item>("중형 힐링 포션", ItemType::Potion,/*가격*/120, 0, 0, 100);
    Itemdb["대형힐링포션"] = make_unique<Item>("대형 힐링 포션", ItemType::Potion,/*가격*/250, 0, 0, 200);
    Itemdb["나무롱소드"] = make_unique<Item>("나무 롱소드", ItemType::Potion,/*가격*/50, 25, 0, 0);
    Itemdb["흑요석롱소드"] = make_unique<Item>("흑요석 롱소드", ItemType::Potion,/*가격*/100, 60, 0, 0);
    Itemdb["철 롱소드"] = make_unique<Item>("흑요석 롱소드", ItemType::Potion,/*가격*/250, 100, 0, 0);
    Itemdb["가죽갑옷"] = make_unique<Item>("가죽 갑옷", ItemType::Potion,/*가격*/50, 0, 0, 30);
    Itemdb["사슬갑옷"] = make_unique<Item>("사슬 갑읏", ItemType::Potion,/*가격*/250, 100, 0, 50);
    Itemdb["철갑옷"] = make_unique<Item>("철 갑옷", ItemType::Potion,/*가격*/250, 100, 0, 100);
    Itemdb["끈적한점액"] = make_unique<Item>("끈적한 점액", ItemType::Expendables,/*가격*/20, 0, 0, 0);
    Itemdb["오크족전투휘장"] = make_unique<Item>("오크족 전투 휘장", ItemType::Expendables,/*가격*/100, 0, 0, 0);
    Itemdb["드래곤 심장"] = make_unique<Item>("드래곤 심장", ItemType::Expendables,/*가격*/300, 0, 0, 0);
    Itemdb["고블린이빨"] = make_unique<Item>("고블린 이빨", ItemType::Expendables,/*가격*/30, 0, 0, 0);
}

ItemManager::~ItemManager() = default;

Item* ItemManager::CreateItem(const ::string& name) {
    auto it = Itemdb.find(name);
    if (it != Itemdb.end()) {
        // 원본을 찾았으면, Clone()을 호출하여 복제품을 만들어 반환
        return it->second->Clone();
    }
    return nullptr; // 해당하는 이름의 아이템이 없으면 nullptr 반환
}