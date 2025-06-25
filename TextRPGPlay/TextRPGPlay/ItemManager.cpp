#include "ItemManager.h"
using namespace std;

ItemManager& ItemManager::Get() {
    static ItemManager instance; // 객체 자체를 static으로
    return instance;
}

ItemManager::ItemManager() {
    Itemdb["소형힐링포션"] = make_unique<Item>("소형 힐링 포션", ItemType::Expendables, 50, 0, 0, 50);
    Itemdb["중형힐링포션"] = make_unique<Item>("중형 힐링 포션", ItemType::Expendables, 120, 0, 0, 100);
    Itemdb["대형힐링포션"] = make_unique<Item>("대형 힐링 포션", ItemType::Expendables, 250, 0, 0, 200);

    // --- 제작 포션  ---
    Itemdb["점액응고포션"] = make_unique<Item>("점액 응고 포션", ItemType::Expendables, 80, 0, 0, 80); // 가성비 상향
    Itemdb["트롤피재생비약"] = make_unique<Item>("트롤 피 재생 비약", ItemType::Expendables, 600, 0, 0, 400); // 가치에 맞게 가격 조정
    Itemdb["열화된재생비약"] = make_unique<Item>("열화된 재생 비약", ItemType::Expendables, 450, 0, 0, 280);
    Itemdb["용심장비약"] = make_unique<Item>("용심장 비약", ItemType::Expendables, 2000, 0, 0, 1200); // 최종 등급에 맞게 성능 및 가격 조정


    // =================================================================================
    // 2. 장비 아이템 (Weapons & Armors)
    // =================================================================================

    // --- 기본 상점 장비 (성능의 기준점 역할) ---
    Itemdb["나무롱소드"] = make_unique<Item>("나무 롱소드", ItemType::Weapon, 50, 25, 0, 0);
    Itemdb["가죽갑옷"] = make_unique<Item>("가죽 갑옷", ItemType::Armor, 50, 0, 30, 0);
    Itemdb["흑요석롱소드"] = make_unique<Item>("흑요석 롱소드", ItemType::Weapon, 150, 60, 0, 0); // 가격 현실화
    Itemdb["사슬갑옷"] = make_unique<Item>("사슬 갑옷", ItemType::Armor, 180, 0, 70, 0);
    Itemdb["철롱소드"] = make_unique<Item>("철 롱소드", ItemType::Weapon, 280, 100, 0, 0);
    Itemdb["철갑옷"] = make_unique<Item>("철 갑옷", ItemType::Armor, 280, 0, 100, 0);


    // --- 제작 장비 (단계별로 구분 및 성능 재조정) ---

    // -- 초급 제작 세트 (고블린/슬라임 재료) --
    Itemdb["고블린톱니단검"] = make_unique<Item>("고블린 톱니 단검", ItemType::Weapon, 90, 45, 0, 0);

    //잡템으로 만들수 있는 갑옷
    Itemdb["누더기갑옷"] = make_unique<Item>("누더기 갑옷", ItemType::Armor, 220, 0, 90, 0);

    // -- 중급 제작 세트 1 (오크 재료) --
    Itemdb["오크어금니도끼"] = make_unique<Item>("오크 어금니 도끼", ItemType::Weapon, 350, 115, 0, 0); // 철 롱소드보다 확실히 좋도록 상향
    Itemdb["오크가죽갑옷"] = make_unique<Item>("오크 가죽 갑옷", ItemType::Armor, 350, 0, 115, 0); // 철갑옷보다 확실히 좋도록 상향

    // -- 중급 제작 세트 2 (트롤 재료) --
    Itemdb["트롤뼈몽둥이"] = make_unique<Item>("트롤뼈 몽둥이", ItemType::Weapon, 500, 140, 0, 0);
    Itemdb["트롤가죽갑옷"] = make_unique<Item>("트롤가죽 갑옷", ItemType::Armor, 500, 0, 140, 0);

    // -- 상급 제작 세트 (수정 - 공백 구간을 메우기 위한 신규 추가) --
    Itemdb["수정의검"] = make_unique<Item>("수정의 검", ItemType::Weapon, 1200, 230, 0, 0);
    Itemdb["수정갑옷"] = make_unique<Item>("수정 갑옷", ItemType::Armor, 1200, 0, 230, 0);

    // -- 최상급 제작 세트 (용 재료) --
    Itemdb["용기사의창"] = make_unique<Item>("용기사의 창", ItemType::Weapon, 3500, 350, 0, 0);
    Itemdb["용기사의갑주"] = make_unique<Item>("용기사의 갑주", ItemType::Armor, 3500, 0, 350, 0);


    // =================================================================================
    // 3. 재료 아이템 (Materials) - 가격만 소폭 조정
    // =================================================================================
    //슬라임
    Itemdb["끈적한점액"] = make_unique<Item>("끈적한 점액", ItemType::Other, 20, 0, 0, 0);
    Itemdb["슬라임핵"] = make_unique<Item>("슬라임 핵", ItemType::Other, 50, 0, 0, 0);

    //고블린
    Itemdb["낡은주머니"] = make_unique<Item>("낡은 주머니", ItemType::Other, 10, 0, 0, 0);
    Itemdb["고블린이빨"] = make_unique<Item>("고블린 이빨", ItemType::Other, 30, 0, 0, 0);
    Itemdb["고블린의귀걸이"] = make_unique<Item>("고블린의 귀걸이", ItemType::Other, 45, 0, 0, 0);
    Itemdb["거친가죽조각"] = make_unique<Item>("거친 가죽 조각", ItemType::Other, 35, 0, 0, 0);

    //오크
    Itemdb["오크힘줄"] = make_unique<Item>("오크 힘줄", ItemType::Other, 40, 0, 0, 0);
    Itemdb["상처난오크등가죽"] = make_unique<Item>("상처 난 오크 등가죽", ItemType::Other, 80, 0, 0, 0);
    Itemdb["오크족전투휘장"] = make_unique<Item>("오크족 전투 휘장", ItemType::Other, 100, 0, 0, 0);
    Itemdb["오크의어금니"] = make_unique<Item>("오크의 어금니", ItemType::Other, 120, 0, 0, 0);
    Itemdb["오크등가죽"] = make_unique<Item>("오크 등가죽", ItemType::Other, 180, 0, 0, 0);


    //트롤
    Itemdb["재생촉매이끼"] = make_unique<Item>("재생 촉매 이끼", ItemType::Other, 500, 0, 0, 0);
    Itemdb["굳어버린트롤의피"] = make_unique<Item>("굳어버린 트롤의 피", ItemType::Other, 150, 0, 0, 0);
    Itemdb["상처난트롤가죽"] = make_unique<Item>("상처 난 트롤 가죽", ItemType::Other, 150, 0, 0, 0);
    Itemdb["트롤의가죽"] = make_unique<Item>("트롤의 가죽", ItemType::Other, 200, 0, 0, 0);
    Itemdb["트롤의재생혈액"] = make_unique<Item>("트롤의 재생 혈액", ItemType::Other, 350, 0, 0, 0);
    Itemdb["트롤의변이된손톱"] = make_unique<Item>("트롤의 변이된 손톱", ItemType::Other, 180, 0, 0, 0);
    //드래곤
    Itemdb["드래곤비늘"] = make_unique<Item>("드래곤 비늘", ItemType::Other, 500, 0, 0, 0);
    Itemdb["드래곤의발톱"] = make_unique<Item>("드래곤의 발톱", ItemType::Other, 750, 0, 0, 0);
    Itemdb["드래곤심장"] = make_unique<Item>("드래곤 심장", ItemType::Other, 1500, 0, 0, 0);

    //기타 아이템
    Itemdb["강화석"] = make_unique<Item>("강화석", ItemType::Other, 50, 0, 0, 0);
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