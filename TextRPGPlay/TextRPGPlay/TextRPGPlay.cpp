// TextRPGPlay.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

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
            cout << GameManager::Get().WrongInputMessage();
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
            GameManager& game = GameManager::Get();
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

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
