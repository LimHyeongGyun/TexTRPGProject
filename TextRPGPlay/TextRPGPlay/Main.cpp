#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void ShowMainMenu() {
    cout << "\n====== 텍스트 RPG ======" << endl;
    cout << "1. 게임 시작" << endl;
    cout << "2. 게임 종료" << endl;
    cout << "========================" << endl;
    cout << "선택: ";
}

int main() {
    int choice;

    while (true) {
        ShowMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "잘못된 입력입니다.\n";
            continue;
        }

        if (choice == 1) {
            cin.ignore(); // 입력 버퍼 정리
            string name;
            cout << "플레이어 캐릭터 이름을 입력하세요: ";
            getline(cin, name);

            // 캐릭터 이름으로 초기화
            Character::Get(name);

            // 게임 실행
            GameManager game;
            game.Run();
        }
        else if (choice == 2) {
            cout << "게임을 종료합니다." << endl;
            break;
        }
        else {
            cout << "1 또는 2만 입력해주세요." << endl;
        }
    }

    return 0;
}