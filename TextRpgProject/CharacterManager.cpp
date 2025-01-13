#include <iostream>
#include <Windows.h>
#include "CharacterManager.h"
#include "Random.h"

using namespace std;

void CharacterManager::CreateCharacter()
{
	bool isComplete = false;
	Character* character = Character::GetInstance();

	character->Init();				// 캐릭터 초기화
	CreateRandomStat(*character);	// 처음 스텟 랜덤설정
	
	string name = "";
	cout << "어서오세요. 캐릭터 생성에 앞서 이름을 정해주세요." << endl;
	cout << "입력: ";
	getline(cin, name);
	
	character->SetName(name);
	cout << "생성하신 플레이어의 이름은 " << name << " 입니다." << endl;
	Sleep(1500);

	while (!isComplete)
	{
		int choice = 0;

		system("cls");
		cout << "캐릭터의 기본 스텟을 정해주세요." << endl;
		cout << "================================" << endl;
		cout << "HP: " << character->stat.HP << endl;
		cout << "MP: " << character->stat.MP << endl;
		cout << "STR: " << character->stat.STR << endl;
		cout << "DEX: " << character->stat.DEX << endl;
		cout << "INT: " << character->stat.INT << endl;
		cout << "LUK: " << character->stat.LUK << endl;
		cout << "================================" << endl;

		cout << "\n플레이어 스텟이 마음에 드시면 완료, 아니면 재설정을 선택해주세요." << endl;
		cout << "1. 완료" << endl;
		cout << "2. 재설정" << endl;
		cout << "선택: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		if (choice == 1)
		{
			cout << "캐릭터 설정이 완료되었습니다. 캐릭터를 생성합니다." << endl;
			Sleep(2000);
			isComplete = true;
		}
		else if (choice == 2)
		{
			CreateRandomStat(*character);
		}
		else
		{
			cout << "잘못된 입력입니다." << endl;
			continue;
		}

	}

	// 설정된 기본스텟에 따른 캐릭터 세부 스텟 결정

}

void CharacterManager::CreateRandomStat(Character& character)
{
	// 캐릭터 스텟은 1 ~ 10 입니다.
	character.stat.HP = GetIntToRandom(1, 10);
	character.stat.MP = GetIntToRandom(1, 10);
	character.stat.STR = GetIntToRandom(1, 10);
	character.stat.DEX = GetIntToRandom(1, 10);
	character.stat.INT = GetIntToRandom(1, 10);
	character.stat.LUK = GetIntToRandom(1, 10);

}