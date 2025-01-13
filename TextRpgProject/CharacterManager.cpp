#include <iostream>
#include <Windows.h>
#include "CharacterManager.h"
#include "Random.h"

using namespace std;

void CharacterManager::CreateCharacter()
{
	bool isComplete = false;
	Character* character = Character::GetInstance();

	character->Init();				// ĳ���� �ʱ�ȭ
	CreateRandomStat(*character);	// ó�� ���� ��������
	
	string name = "";
	cout << "�������. ĳ���� ������ �ռ� �̸��� �����ּ���." << endl;
	cout << "�Է�: ";
	getline(cin, name);
	
	character->SetName(name);
	cout << "�����Ͻ� �÷��̾��� �̸��� " << name << " �Դϴ�." << endl;
	Sleep(1500);

	while (!isComplete)
	{
		int choice = 0;

		system("cls");
		cout << "ĳ������ �⺻ ������ �����ּ���." << endl;
		cout << "================================" << endl;
		cout << "HP: " << character->stat.HP << endl;
		cout << "MP: " << character->stat.MP << endl;
		cout << "STR: " << character->stat.STR << endl;
		cout << "DEX: " << character->stat.DEX << endl;
		cout << "INT: " << character->stat.INT << endl;
		cout << "LUK: " << character->stat.LUK << endl;
		cout << "================================" << endl;

		cout << "\n�÷��̾� ������ ������ ��ø� �Ϸ�, �ƴϸ� �缳���� �������ּ���." << endl;
		cout << "1. �Ϸ�" << endl;
		cout << "2. �缳��" << endl;
		cout << "����: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "���ڸ� �Է°����մϴ�." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		if (choice == 1)
		{
			cout << "ĳ���� ������ �Ϸ�Ǿ����ϴ�. ĳ���͸� �����մϴ�." << endl;
			Sleep(2000);
			isComplete = true;
		}
		else if (choice == 2)
		{
			CreateRandomStat(*character);
		}
		else
		{
			cout << "�߸��� �Է��Դϴ�." << endl;
			continue;
		}

	}

	// ������ �⺻���ݿ� ���� ĳ���� ���� ���� ����

}

void CharacterManager::CreateRandomStat(Character& character)
{
	// ĳ���� ������ 1 ~ 10 �Դϴ�.
	character.stat.HP = GetIntToRandom(1, 10);
	character.stat.MP = GetIntToRandom(1, 10);
	character.stat.STR = GetIntToRandom(1, 10);
	character.stat.DEX = GetIntToRandom(1, 10);
	character.stat.INT = GetIntToRandom(1, 10);
	character.stat.LUK = GetIntToRandom(1, 10);

}