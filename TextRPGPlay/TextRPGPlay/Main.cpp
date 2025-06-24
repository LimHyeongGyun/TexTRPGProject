#include "GameManager.h"
#include "Character.h"
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void ShowMainMenu() {
    cout << "\n====== �ؽ�Ʈ RPG ======" << endl;
    cout << "1. ���� ����" << endl;
    cout << "2. ���� ����" << endl;
    cout << "========================" << endl;
    cout << "����: ";
}

int main() {
    int choice;

    while (true) {
        ShowMainMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "�߸��� �Է��Դϴ�.\n";
            continue;
        }

        if (choice == 1) {
            cin.ignore(); // �Է� ���� ����
            string name;
            cout << "�÷��̾� ĳ���� �̸��� �Է��ϼ���: ";
            getline(cin, name);

            // ĳ���� �̸����� �ʱ�ȭ
            Character::Get(name);

            // ���� ����
            GameManager game;
            game.Run();
        }
        else if (choice == 2) {
            cout << "������ �����մϴ�." << endl;
            break;
        }
        else {
            cout << "1 �Ǵ� 2�� �Է����ּ���." << endl;
        }
    }

    return 0;
}