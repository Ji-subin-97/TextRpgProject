#include <iostream>
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
	cout << "피해감소율: " << character->GetDamageReduction() << " % | " << "명중률: " << character->GetAccuracy() << " % " << endl;
	cout << "스킬강화율: " << character->GetSkillEnhancement() << " % | " << "치명타확률: " << character->GetCriticalChance() << " % " << endl;
	cout << character->GetLevel() << " LV | " << character->GetExperience() << " EXP | " << character->GetGold() << " 원" << endl;
	cout << "==========================================================================" << endl;

	for (Monster* monster : monsters)
	{
		if (monster != nullptr)
		{
			if (monster->GetHealth() > 0)
			{
				cout << "==========================================================================" << endl;
				cout << monster->GetName() << " | " << monster->GetHealth() << " HP | " << monster->GetAttack() << " AD" << endl;
				cout << "==========================================================================" << endl;
			}
			else
			{
				cout << "==========================================================================" << endl;
				cout << monster->GetName() << " *  토벌완료 * " << endl;
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

	for (int i = 0; i < battleLevel; i++)
	{
		monsters.push_back(monsterManager.CreateMonster(battleLevel, character->GetLevel()));
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
	bool isEndBattle = false;		// 전투종료 여부
	bool isRun = false;				// 플레이어 도망여부
	int monsterDieCount = 0;		// 몬스터 처치수
	const vector<Monster*>& monsters = battle->GetMonsters();

	for (int i = 0; i < monsters.size(); i++)
	{
		bool isMonsterDie = false;	// i번째 몬스터 처치여부
		if (isEndBattle || isRun) break;

		while (!isEndBattle)
		{
			PrintBattleStatus();
			isRun = battle->PlayerTurn(monsters[i]);

			if (isRun)
			{
				break;
			}

			isMonsterDie = battle->MonsterTurn(monsters[i]);

			if (isMonsterDie) {
				monsterDieCount++;

				if (monsterDieCount == monsters.size())
				{
					isEndBattle = true; // 모든 몬스터 토벌시 전투종료
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
			message = "모든 몬스터를 처치하였습니다.";
		}
		else
		{
			message = "도망쳤습니다.";
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

	delete battle;	// Battle 및 Monster 메모리 해제
}

int BattleManager::GetBattleLevel() const
{
	return battleLevel;
}

void BattleManager::SetBattleLevel(int battleLevel)
{
	this->battleLevel = battleLevel;
}