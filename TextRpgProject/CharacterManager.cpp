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

		// ó�� ������ �⺻���ݿ� ���� ĳ���� ���� ���� ����
		GenerateCharacter(*character, true);
	}
	else
	{
		cout << "ĳ���� ������ �����Ͽ����ϴ�. �����ڿ��� �������ּ���." << endl;
	}

}

Character* CharacterManager::GetCharacter()
{
	Character* character = Character::GetInstance();

	if (character == nullptr) {
		cout << "ĳ���Ͱ� ���������ʽ��ϴ�." << endl;
	}

	return character;
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

void CharacterManager::GenerateCharacter(Character& character, bool isFirst)
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

	if (isFirst)
	{
		character.SetHp(HP);
		character.SetMp(MP);
	}

	character.SetMaxHp(HP);
	character.SetMaxMp(MP);
	character.SetAttack(ATTACK);
	character.SetDamageReduction(character.GetCharacterStat().STR + 1);
	character.SetAccuracy(character.GetCharacterStat().DEX + 50);
	character.SetSkillEnhancement(character.GetCharacterStat().INT * 5);
	character.SetCriticalChance(character.GetCharacterStat().LUK * 2);
	character.SetStatStockAll(
		character.GetCharacterStat().STR
		+ character.GetCharacterStat().DEX
		+ character.GetCharacterStat().INT
		+ character.GetCharacterStat().LUK);
}

void CharacterManager::PrintCharacterInfoAll()
{
	Character* character = Character::GetInstance();
	system("cls");
	if (character != nullptr)
	{
		cout << "\n====================================================================" << endl;
		cout << "[ " << character->GetName() << " ] ���� �ɷ�ġ�Դϴ�." << endl;
		cout << " * ����: " << character->GetLevel() <<  " LV" << endl;
		cout << " * HP: " << character->GetHp() << " / " << character->GetMaxHp() << endl;
		cout << " * MP: " << character->GetMp() << " / " << character->GetMaxMp() << endl;
		cout << " * ���ݷ�: " << character->GetAttack() << endl;
		PrintCharacterInfoStat(character->GetCharacterStat());
		cout << " * ���: " << character->GetDamageReduction() << endl;
		cout << " * ���߷�: " << character->GetAccuracy() << " %" << endl;
		cout << " * ��ų������������: " << character->GetSkillEnhancement() << " %" << endl;
		cout << " * ġ��Ÿ��: " << character->GetCriticalChance() << " %" << endl;
		cout << " * ����ġ: " << character->GetExperience() << " / " << character->GetExperienceCapacity() << endl;
		cout << " * ���: " << character->GetGold() << " ��" << endl;
		cout << "====================================================================" << endl;
	}
	else
	{
		cout << "ĳ���Ͱ� �������� �ʽ��ϴ�...." << endl;
	}

}

void CharacterManager::PrintCharacterInfoStat(CharacterStat stat)
{
	cout << " * STR: " << stat.STR << endl;
	cout << " * DEX: " << stat.DEX << endl;
	cout << " * INT: " << stat.INT << endl;
	cout << " * LUK: " << stat.LUK << endl;

}

void CharacterManager::SetCharacterStat()
{
	int choice = 0;
	bool isComplete = false;

	Character* character = Character::GetInstance();
	if (character != nullptr)
	{
		
		CharacterStat stat = character->GetCharacterStat();
		int statStock = character->GetStatStock();

		while (!isComplete)
		{
			system("cls");
			cout << "���� �÷��̾��� ���� �����Դϴ�.===========================" << endl;
			PrintCharacterInfoStat(stat);
			cout << "===========================================================" << endl;
			cout << "��������: " << statStock << " POINT" << endl;
			cout << "[1]. STR �� / [2]. STR ��" << endl;
			cout << "[3]. DEX �� / [4]. DEX ��" << endl;
			cout << "[5]. INT �� / [6]. INT ��" << endl;
			cout << "[7]. LUK �� / [8]. LUK ��" << endl;
			cout << "[9]. �����ϱ�" << endl;
			cout << "[0]. �ڷΰ���" << endl;
			cout << "����: ";
			cin >> choice;

			if (cin.fail())
			{
				cout << "���ڸ� �Է°����մϴ�." << endl;
				Sleep(500);
				cin.clear();
				cin.ignore();

				continue;
			}

			// �ڷΰ���
			if (choice == 0)
			{
				break;
			}

			// �����ϱ�
			if (choice == 9)
			{
				character->SetStatStock(statStock);
				character->SetCharacterStat(stat);
				GenerateCharacter(*character, false);
				break;
			}

			// �ʰ��ؼ� ���� ���ϵ���
			if (statStock == character->GetStatStock() && choice % 2 == 0)
			{
				continue;
			}

			if (statStock > 0 || choice % 2 == 0)
			{
				switch (choice)
				{
				case 1:
					stat.STR++;
					statStock--;
					break;
				case 2:
					if (stat.STR > 0)
					{
						stat.STR--;
						statStock++;
					}
					break;
				case 3:
					stat.DEX++;
					statStock--;
					break;
				case 4:
					if (stat.DEX > 0)
					{
						stat.DEX--;
						statStock++;
					}
					break;
				case 5:
					stat.INT++;
					statStock--;
					break;
				case 6:
					if (stat.INT > 0)
					{
						stat.INT--;
						statStock++;
					}
					break;
				case 7:
					stat.LUK++;
					statStock--;
					break;
				case 8:
					if (stat.LUK > 0)
					{
						stat.LUK--;
						statStock++;
					}
					break;
				default:
					cout << "�߸��� �Է��Դϴ�." << endl;
					Sleep(500);
					break;
				}
			}
			else
			{
				cout << "�ɷ�ġ�� �ø� ������ �������� �ʽ��ϴ�." << endl;
				Sleep(1000);
				continue;
			}

		}
	}

}

void CharacterManager::SetCharacterStatAfterLevelUp()
{
	Character* character = Character::GetInstance();

	system("cls");
	cout << "���ϵ帳�ϴ� ĳ���Ͱ� " << character->GetLevel() << " LV ���� �������Ͽ����ϴ�!" << endl;
	cout << "����� ���Ȱ���â���� �Ѿ�ϴ�." << endl;
	Sleep(3000); 

	SetCharacterStat();
	// ĳ���� ���� ������ �ķ� �缳�� �� ȸ�� �� ����ġ ����
	character->SetHp(character->GetMaxHp());
	character->SetMp(character->GetMaxMp());

	// ������
	SetCharacterExp(1);
}

void CharacterManager::SetCharacterExp(int caseNum) // caseNum 1: ������, 2: ���
{
	Character* character = Character::GetInstance();
	int exp = character->GetExperience();
	int expCapacity = character->GetExperienceCapacity();

	if (caseNum == 1)
	{
		// ���� ����ġ exp - expCapacity;
		character->SetExperience(exp - expCapacity);
		// �� �Ŀ� ����ġ �ѷ��� ���� �ѷ��� ĳ���ͷ��� * 10 �� ������
		character->SetExperienceCapacity(expCapacity + character->GetLevel() * 10);
	}
	else
	{
		// ���? 
	}

	// ���� ����ġ�� �����̸� 0���� �ʱ�ȭ
	if (character->GetExperience())
	{
		character->SetExperience(0);
	}

}

// ============================= ��ų ���� =======================================
void CharacterManager::CharacterGetSkill()
{
	Character* character = Character::GetInstance();
	SkillManager* skillManager = SkillManager::GetInstance();
	unique_ptr<Skill> skill = skillManager->TakeSkillRandom();

	if (skill != nullptr)
	{
		character->TakeSkill(move(skill));
	}
}