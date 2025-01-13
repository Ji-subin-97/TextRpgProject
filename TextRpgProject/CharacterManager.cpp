#include <iostream>
#define NOMINMAX
#include <Windows.h>
#include <algorithm>
#include "CharacterManager.h"
#include "Random.h"

using namespace std;

void CharacterManager::CreateCharacter()
{
	bool isComplete = false;
	Character* character = Character::GetInstance();

	if (character != nullptr)
	{
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
			cout << "HP: " << character->GetCharacterStat().HP << endl;
			cout << "MP: " << character->GetCharacterStat().MP << endl;
			cout << "STR: " << character->GetCharacterStat().STR << endl;
			cout << "DEX: " << character->GetCharacterStat().DEX << endl;
			cout << "INT: " << character->GetCharacterStat().INT << endl;
			cout << "LUK: " << character->GetCharacterStat().LUK << endl;
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
		GenerateCharacter(*character);
	}
	else
	{
		cout << "캐릭터 생성에 실패하였습니다. 관리자에게 문의해주세요." << endl;
	}

}

void CharacterManager::CreateRandomStat(Character& character)
{
	// 캐릭터 스텟은 1 ~ 10 입니다.
	CharacterStat stat = character.GetCharacterStat();
	stat.HP = GetIntToRandom(1, 10);
	stat.MP = GetIntToRandom(1, 10);
	stat.STR = GetIntToRandom(1, 10);
	stat.DEX = GetIntToRandom(1, 10);
	stat.INT = GetIntToRandom(1, 10);
	stat.LUK = GetIntToRandom(1, 10);

	character.SetCharacterStat(stat);
}

void CharacterManager::GenerateCharacter(Character& character)
{
	/* 계산공식
	*  체력 및 최대체력: 기본100 + (HP * 캐릭터레벨 * 10)
	   마나 및 최대마나: 기본50 + (MP * 캐릭터레벨 * 5)
	   공격력: 기본10 + ( (STR, DEX, LUK중 높은거) + 캐릭터레벨 * 5)
	   
	   피해감소율: STR++
	   명중률 : 기본 50.0 + DEX++
	   스킬강화 : INT * 5
	   치명타: LUK * 2
	*/
	int charLevel = character.GetLevel();

	int HP = 100 + (character.GetCharacterStat().HP * charLevel * 10);
	int MP = 50 + (character.GetCharacterStat().MP * charLevel * 5);
	int ATTACK = 10 + 
		(std::max({ character.GetCharacterStat().STR
			, character.GetCharacterStat().DEX
			, character.GetCharacterStat().LUK }) + charLevel * 5);

	character.SetHp(HP);
	character.SetMaxHp(HP);
	character.SetMp(MP);
	character.SetMaxMp(MP);
	character.SetAttack(ATTACK);
	character.SetDamageReduction(character.GetCharacterStat().STR + 1);
	character.SetAccuracy(character.GetCharacterStat().DEX + 50);
	character.SetSkillEnhancement(character.GetCharacterStat().INT * 5);
	character.SetCriticalChance(character.GetCharacterStat().LUK * 2);
}

void CharacterManager::PrintCharacterInfo()
{
	Character* character = Character::GetInstance();
	if (character != nullptr)
	{
		system("cls");
		cout << "\n====================================================================" << endl;
		cout << "[ " << character->GetName() << " ] 님의 능력치입니다." << endl;
		cout << " * 레벨: " << character->GetLevel() <<  " LV" << endl;
		cout << " * HP: " << character->GetHp() << " / " << character->GetMaxHp() << endl;
		cout << " * MP: " << character->GetMp() << " / " << character->GetMaxMp() << endl;
		cout << " * 공격력: " << character->GetAttack() << endl;
		cout << " * STR: " << character->GetCharacterStat().STR << endl;
		cout << " * DEX: " << character->GetCharacterStat().DEX << endl;
		cout << " * INT: " << character->GetCharacterStat().INT << endl;
		cout << " * LUK: " << character->GetCharacterStat().LUK << endl;
		cout << " * 방어율: " << character->GetDamageReduction() << " %" << endl;
		cout << " * 명중률: " << character->GetAccuracy() << " %" << endl;
		cout << " * 스킬데미지증가율: " << character->GetSkillEnhancement() << " %" << endl;
		cout << " * 치명타율: " << character->GetCriticalChance() << " %" << endl;
		cout << "====================================================================" << endl;
	}

}