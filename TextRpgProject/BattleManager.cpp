#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <iomanip>
#include "BattleManager.h"
#include "MonsterManager.h"

using namespace std;

void BattleManager::Init()
{
	battleLevel = 1;
}

void BattleManager::PrintBattleStatus()
{
	const Character* character = battle->GetCharacter();
	const vector<Monster*>& monsters = battle->GetMonsters();

	system("cls");

	cout << "==========================================================================" << endl;
	cout << character->GetName() << " | " << character->GetHp() << " HP | " << character->GetMp() << " MP" << endl;
	cout << "���ذ���: " << character->GetDamageReduction() << " | " << "���߷�: " << character->GetAccuracy() << " % " << endl;
	cout << "��ų��ȭ��: " << character->GetSkillEnhancement() << " % | " << "ġ��ŸȮ��: " << character->GetCriticalChance() << " % " << endl;
	cout << character->GetLevel() << " LV | " << character->GetExperience() << " EXP | " << character->GetGold() << " ��" << endl;
	cout << "==========================================================================" << endl;

	for (Monster* monster : monsters)
	{
		if (monster != nullptr)
		{
			if (monster->GetHealth() > 0)
			{
				cout << "==========================================================================" << endl;
				if (monster->IsBoss()) {
					cout << "���� ����" << endl;
				}
				cout << monster->GetName() << " | " << monster->GetHealth() << " HP | " << monster->GetAttack() << " AD" << endl;
				cout << "==========================================================================" << endl;
			}
			else
			{
				cout << "==========================================================================" << endl;
				cout << monster->GetName() << " *  ����Ϸ� * " << endl;
				cout << "==========================================================================" << endl;
			}
		}
	}
}

void BattleManager::PrintBattleResult()
{

}

bool BattleManager::CreateBattle(int battleLevel, Character* character)
{

	MonsterManager monsterManager;
	vector<Monster*> monsters;
	int playerLevel = character->GetLevel();

	// �÷��̾� ������ 10�ϰ�� ������ �⿬
	if (playerLevel >= 10)
	{
		monsters.push_back(monsterManager.CreateBossMonster());
	}
	else
	{
		for (int i = 0; i < battleLevel; i++)
		{
			monsters.push_back(monsterManager.CreateMonster(battleLevel, character->GetLevel()));
		}
	}

	battle = new Battle(character, monsters, battleLevel);

	if (battle != nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}

}

void BattleManager::StartBattle()
{
	system("cls");
	bool isEndBattle = false;		// �������� ����
	bool isRun = false;				// �÷��̾� ��������
	int monsterDieCount = 0;		// ���� óġ��
	const vector<Monster*>& monsters = battle->GetMonsters();

	for (int i = 0; i < monsters.size(); i++)
	{
		bool isMonsterDie = false;	// i��° ���� óġ����
		if (isEndBattle || isRun) break;

		// ó�� ���� �÷��̾� �� ����
		battle->SetIsPlayerTurn(true);

		while (!isEndBattle)
		{
			PrintBattleStatus();

			if (battle->GetIsPlayerTurn())
			{
				isRun = battle->PlayerTurn(monsters[i]);
			}
			if (isRun)
			{
				break;
			}

			if (battle->GetIsMonsterTurn())
			{
				isMonsterDie = battle->MonsterTurn(monsters[i]);
			}
			
			if (isMonsterDie) {
				monsterDieCount++;

				if (monsterDieCount == monsters.size())
				{
					isEndBattle = true; // ��� ���� ����� ��������
				}

				break;
			}
		}
	}

	if (isEndBattle || isRun)
	{
		string message;

		if (isEndBattle)
		{
			message = "��� ���͸� óġ�Ͽ����ϴ�.";
		}
		else
		{
			message = "�����ƽ��ϴ�.";
		}

		EndBattle(message);
		return;
	}

}

void BattleManager::EndBattle(const string& message)
{
	const Character* character = battle->GetCharacter();

	system("cls");
	cout << "==========================================================" << endl;
	cout << "| " << message << endl;
	cout << "==========================================================" << endl;
	Sleep(2000);

	delete battle;	// Battle �� Monster �޸� ����
}

int BattleManager::GetBattleLevel() const
{
	return battleLevel;
}

void BattleManager::SetBattleLevel(int battleLevel)
{
	this->battleLevel = battleLevel;
}