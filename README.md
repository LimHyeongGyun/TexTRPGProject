# 🎮 Text Rpg 프로젝트 <10조>

## **👥 프로젝트 참여 인원**

- 천재우 - 팀장: Game Manager, Main Framework 및 ReadMe 담당
- 임형균 - 부팀장: Forge, Character, Inventroy 담당
- 안지호 - 팀원: Item, Item Manager 담당
- 이정민 - 팀원: Monster 담당
- 황순호 - 팀원: PPT, Flow Chart, 발표 담당

<br>

## **📅 개발 일정 요약**

| 날짜       | 작업 내용                    | 담당자   |
|------------|-----------------------------|----------|
| 6/19 ~ 6/23 | 프로젝트 구조 설계 및 클래스 정의 | 코드 담당 협업 |
| 6/24 ~ 6/26 | 코드 수정 및 마무리 작업    | 코드 담당 협업    |
| 6/26 ~ 6/27 | PPT, Flow Chart 제작      | 발표 담당 제작 |

<br>

## **🖥️ 프로젝트 정보**
- 프로젝트 명: Text Rpg 
- 개발엔진: C++
- 개발개요: 내일배움캠프 C++ 프로젝트

<br>

## **⚙️ 작동 환경**
- 운영체제: Windows (콘솔 기반)
- 권장 C++ 표준: C++17 이상
- 컴파일러: Visual Studio / g++ / clang 등

<br>

## **🛠️ 주요 기능**
- 캐릭터 생성 및 능력치 확인
- 전투 시스템 (공격 / 아이템 사용 / 도망)
- 인벤토리 시스템 (소모품, 무기, 방어구, 기타)
- 대장간 방문 → 장비 강화 가능
- 상점 방문 → 아이템 구매/판매 가능
- 레벨 10 도달 시 드래곤 등장, 처치 시 게임 종료

<br>

## **🧠 사용된 기술 / 학습한 내용**

- 클래스 설계 및 상속
- 싱글톤 패턴
- 프로토타입 패턴
- C++ 포인터, new/delete 메모리 관리
- 조건문/반복문 기반 전투 시뮬레이션

<br>

## **🎮 게임 흐름**

- 게임 시작
- 대기 상태 메뉴에서 인벤토리, 대장간, 상점, 전투 중에 선택 
- 플레이어 레벨에 따라 몬스터 등장 (슬라임 ~ 고블린)
- 레벨 10 도달 시 보스 몬스터 드래곤 등장
- 드래곤 처치 시 게임 클리어

<br>

## **🔧 클래스 구조**

| 클래스         | 설명                            |
|----------------|---------------------------------|
| GameManager  | 게임 전체 흐름 제어             |
| Character    | 플레이어 정보                    |
| Monster      | 몬스터 기본 클래스               |
| Slime~Dragon| 레벨별 몬스터 상속클래스           |
| Inventory    | 플레이어의 아이템 관리           |
| ItemManager  | 아이템 원형 등록 및 복제         |
| Forge        | 장비 강화 기능                   |
| Store        | 상점에서 아이템 구매 및 판매      |

<br>

## **💣 트러블 슈팅**

| 버그 항목 | 설명 |
|-----------|------|
| 아이템 타입 분류 오류 | `ItemType을` `enum class`로 분류하였지만, 기타 아이템, 소비 아이템 등의 처리 로직이 달라 필요에 따라 `Use()` 함수의 오버라이딩(`Overriding`) 구조 적용 → `Other`, `Expendable` 등 세분화하여 대응 |
| 장비 장착 처리 오류 | `Weapon::Use()` 및 `Armor::Use()`에서 `Character`에서 직접 장착 처리 → `Inventory::EquipWeapon()` 등으로 책임 분리하여 해결 |
| 장비 강화 처리 | 강화 수치(`upgradeAtkValue`, `upgradeHpValue`)가 `Item`에 있었으나, `Forge`에서 강화 처리하는 게 더 적절하여 기능 이전 |
| 아이템 제거 처리 오류 | 소비 아이템 사용 시 수량이 줄지 않음 → `Inventory::RemoveNoneEquipItem()`으로 수량 감소 처리 추가 |
| 상점 판매 로직 반복 문제 | 빈 인벤토리에서 반복적으로 나가기 선택 시 나갈 수 없는 문제 발생 → 조건문 분기 및 `break`,`return` 처리로 해결 |
| 판매 시 수량 및 존재 여부 미확인 | 입력된 아이템이 실제로 존재하지 않거나 수량이 부족할 때도 판매 진행됨 → 이름 확인 및 수량 비교 로직 추가로 해결 |
| 드래곤 출력 오류 | 레벨 10 이상이 되어도 드래곤이 등장하지 않거나, 처치 후 게임이 종료되지 않는 문제 발생 → `Battle()` 내에서 드래곤 식별 후 `exit(0)` 처리로 종료 구현 |

<br>

## **📖 Text RPG 아이템 데이터터**
- https://docs.google.com/spreadsheets/d/1aA2sDAyZF77xMp9tFCXwEXo6a4sWK0WscnOHQ2ESNQY/edit?gid=0#gid=0

<br>

## **📈 Flow Chart**

- GameManager
게임의 전체 흐름을 제어하며, 캐릭터와 몬스터 간의 전투 및 상태 전환을 관리합니다.<br>
→ Character와 Monster를 직접 생성하고 연결합니다.

- Character (플레이어)
플레이어의 정보(이름, 체력, 레벨 등)를 저장하고, 공격, 아이템 사용 등 주요 행위를 담당합니다.<br>
→ Inventory를 포함하여 아이템 장착 및 소비 기능을 제공합니다.

- Inventory (인벤토리)
무기, 방어구, 소모품 등 아이템을 저장 및 관리합니다.<br>
→ 아이템 사용 시 Character에게 영향을 줍니다.<br>
→ 돈(Gold)을 보유하며, 아이템 구매/판매 기능과 연결됩니다.

- Item (아이템)
무기, 방어구, 소모품 등으로 구분되며, 공통 부모 클래스를 상속받아 Use()를 오버라이딩합니다.<br>
→ 인벤토리에 저장되며, 전투 및 강화 시스템과 연결됩니다.

- Monster (적 개체)
Slime, Orc, Troll, Goblin 등 일반 몬스터와 보스 몬스터 Dragon으로 구분됩니다.<br>
→ 전투 중 캐릭터와 상호 작용하며, 처치 시 아이템/골드/경험치를 드랍합니다.

- Gold (돈)
아이템 구매, 판매, 강화 시 소비되며, Character와 Inventory에서 관리됩니다.

<br>

## **🎮 게임 시행**
- ### 게임 시작화면
![게임시작화면](https://github.com/user-attachments/assets/7bd77c3d-d3d6-42fc-b6c2-017e51373215)<br>

- ### 캐릭터 이름 설정
![캐릭터 이름 설정](https://github.com/user-attachments/assets/9a6041b7-6bf4-4db0-b1a8-f557d93c626b)<br>

- ### 게임 대기화면
![대기화면모습](https://github.com/user-attachments/assets/9b7cb8f0-a1e6-468c-abd3-a8de8fad142d)<br>

- ### 캐릭터의 상태창
![캐릭터의 상태창 모습](https://github.com/user-attachments/assets/5fa0cc06-7f1e-406c-86e1-716babe3ca4b)<br>

- ### 몬스터와 전투
![몬스터와 전투하기](https://github.com/user-attachments/assets/59d9da7b-ca37-47b7-b73a-8ef2de4154bc)<br>

- ### 캐릭터 레벨업
![몬스터를 잡고 레벨업](https://github.com/user-attachments/assets/5880fc44-58ab-4ebe-87ba-e02c9a5f07f7)<br>

- ### 인벤토리 창 출력
![인벤토리 창 출력](https://github.com/user-attachments/assets/01dd9c00-cd44-4b72-bdfe-773018873b40)<br>

- ### 기타 아이템 확인
![획득한 기타 아이템 확인](https://github.com/user-attachments/assets/d4b521e3-3bfc-44a1-ab74-76edddd1c7e7)<br>

- ### 상점 방문 후 아이템 판매
![상점에 방문하여 획득한 기타 아이템 판매](https://github.com/user-attachments/assets/6627e1d9-82e3-4e85-b64c-409199a2b897)<br>

- ### 골드로 무기 구입 
![회득한 골드로 무기 구입](https://github.com/user-attachments/assets/ad56b6a3-832d-42d7-bad5-1f93e8358472)<br>

- ### 힐포션 구입 
![추가로 힐포션 구매](https://github.com/user-attachments/assets/bbc52aa9-3ac3-43c0-9b12-d64357f3902a)<br>

- ### 전투 중 회복아이템 사용 
![전투시 회복아이템 사용](https://github.com/user-attachments/assets/808f5a4e-cb0a-48f6-87fd-342adf7dc35e)<br>

- ### 드래곤 처치 후 게임 끝
![드래곤 처치 후 게임 끝](https://github.com/user-attachments/assets/a09adff9-1139-4d5e-b997-5a34efd82bb4)<br>



