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
			cout << "HP: " << character->GetCharacterStat().HP << endl;
			cout << "MP: " << character->GetCharacterStat().MP << endl;
			cout << "STR: " << character->GetCharacterStat().STR << endl;
			cout << "DEX: " << character->GetCharacterStat().DEX << endl;
			cout << "INT: " << character->GetCharacterStat().INT << endl;
			cout << "LUK: " << character->GetCharacterStat().LUK << endl;
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
		GenerateCharacter(*character);
	}
	else
	{
		cout << "ĳ���� ������ �����Ͽ����ϴ�. �����ڿ��� �������ּ���." << endl;
	}

}

void CharacterManager::CreateRandomStat(Character& character)
{
	// ĳ���� ������ 1 ~ 10 �Դϴ�.
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
	/* ������
	*  ü�� �� �ִ�ü��: �⺻100 + (HP * ĳ���ͷ��� * 10)
	   ���� �� �ִ븶��: �⺻50 + (MP * ĳ���ͷ��� * 5)
	   ���ݷ�: �⺻10 + ( (STR, DEX, LUK�� ������) + ĳ���ͷ��� * 5)
	   
	   ���ذ�����: STR++
	   ���߷� : �⺻ 50.0 + DEX++
	   ��ų��ȭ : INT * 5
	   ġ��Ÿ: LUK * 2
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
		cout << "[ " << character->GetName() << " ] ���� �ɷ�ġ�Դϴ�." << endl;
		cout << " * ����: " << character->GetLevel() <<  " LV" << endl;
		cout << " * HP: " << character->GetHp() << " / " << character->GetMaxHp() << endl;
		cout << " * MP: " << character->GetMp() << " / " << character->GetMaxMp() << endl;
		cout << " * ���ݷ�: " << character->GetAttack() << endl;
		cout << " * STR: " << character->GetCharacterStat().STR << endl;
		cout << " * DEX: " << character->GetCharacterStat().DEX << endl;
		cout << " * INT: " << character->GetCharacterStat().INT << endl;
		cout << " * LUK: " << character->GetCharacterStat().LUK << endl;
		cout << " * �����: " << character->GetDamageReduction() << " %" << endl;
		cout << " * ���߷�: " << character->GetAccuracy() << " %" << endl;
		cout << " * ��ų������������: " << character->GetSkillEnhancement() << " %" << endl;
		cout << " * ġ��Ÿ��: " << character->GetCriticalChance() << " %" << endl;
		cout << "====================================================================" << endl;
	}

}