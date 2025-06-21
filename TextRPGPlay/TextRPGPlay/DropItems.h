#pragma once

#include <string>

using namespace std;

enum class ItemType {
	SlimeGel,
	OrcBattleBadge,
	TrollLeather,
	GoblinTooth,
	DragonHeart,

	Gold1,
	Gold3,
	Gold5,
	Gold10,
	Gold1000
};

inline string getItemName(ItemType item) {
	switch (item) {
	case ItemType::SlimeGel: return "끈적한 점액";
	case ItemType::OrcBattleBadge: return "오크족 전투 휘장";
	case ItemType::TrollLeather: return "트롤 가죽";
	case ItemType::GoblinTooth: return "고블린 이빨";
	case ItemType::DragonHeart: return "드래곤 심장";

	case ItemType::Gold1: return "구겨진 동전 주머니(1G)";
	case ItemType::Gold3: return "무게감 있는 주머니(3G)";
	case ItemType::Gold5: return "묵직한 금화 주머니(5G)";
	case ItemType::Gold10: return "화려한 금화 자루(10G)";
	case ItemType::Gold1000: return "전설의 금화 상자(1000G)";
	default: return "알 수 없는 아이템";
	}
}