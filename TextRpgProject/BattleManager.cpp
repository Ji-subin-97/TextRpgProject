#include <iostream>
#include <format>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <iomanip>
#include "BattleManager.h"
#include "MonsterManager.h"
#include "CharacterManager.h"
#include "Renderer.h"
#include "GameMap.h"
#include "Cursor.h"
#include "LogBox.h"

using namespace std;

void BattleManager::Init()
{
	battleLevel = 1;
}

void BattleManager::PrintBattleStatus()
{
	const Character* character = battle->GetCharacter();
	const vector<Monster*>& monsters = battle->GetMonsters();

	for (Monster* monster : monsters)
	{
		if (monster != nullptr)
		{
			if (monster->GetHealth() > 0)
			{
				if (monster->IsBoss())
				{
					LogBox::GetInstance()->Print("최종 보스", RGB(255, 128, 0));
				}
				LogBox::GetInstance()->Print(format("{} | {} HP | {} AD", monster->GetName(), monster->GetHealth(), monster->GetAttack()), RGB(255,255,0));
			}
			else
			{
				LogBox::GetInstance()->Print(format("{} * 토벌완료 *", monster->GetName()),RGB(128,255,0));
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

	// 플레이어 레벨이 10일경우 보스몹 출연
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
	bool isEndBattle = false;		// 전투종료 여부
	bool isRun = false;				// 플레이어 도망여부
	int monsterDieCount = 0;		// 몬스터 처치수
	const vector<Monster*>& monsters = battle->GetMonsters();

	Renderer::GetInstance()->SelectMap(GameMap::Battle());

	for (int i = 0; i < monsters.size(); i++)
	{
		bool isMonsterDie = false;	// i번째 몬스터 처치여부
		if (isEndBattle || isRun) break;

		// 처음 턴은 플레이어 턴 고정
		battle->SetIsPlayerTurn(true);

		// 캐릭터 이름 렌더링
		string name = Character::GetInstance()->GetName();
		Renderer::GetInstance()->EditText(31, name);
		Renderer::GetInstance()->ExpandText(31, 1, 0);

		//몬스터 체력바 렌더링
		int enemyHp = monsters[i]->GetHealth();
		int enemyMaxHp = monsters[i]->GetHealth();
		int currentEnemyHp = enemyHp * 80 / enemyMaxHp;
		string enemyName = monsters[i]->GetName();

		Renderer::GetInstance()->EditText(41, enemyName);
		Renderer::GetInstance()->ExpandText(41, 1, 0);
		Renderer::GetInstance()->EditText(51, format("{} / {}", enemyHp, enemyMaxHp));
		Renderer::GetInstance()->SetTextBackgroundColor(51, RGB(192, 0, 0), currentEnemyHp);

		while (!isEndBattle)
		{
			//캐릭터 체력바 렌더링
			int hp = Character::GetInstance()->GetHp();
			int mp = Character::GetInstance()->GetMp();
			int exp = Character::GetInstance()->GetExperience();
			int maxHp = Character::GetInstance()->GetMaxHp();
			int maxMp = Character::GetInstance()->GetMaxMp();
			int maxExp = Character::GetInstance()->GetExperienceCapacity();
			int currentHp = hp * 80 / maxHp;
			int currentMp = mp * 80 / maxMp;
			int currentExp = exp * 80 / maxExp;

			Renderer::GetInstance()->EditText(21, format("{} / {}", hp, maxHp));
			Renderer::GetInstance()->EditText(22, format("{} / {}", mp, maxMp));
			Renderer::GetInstance()->EditText(23, format("{} / {}", exp, maxExp));

			Renderer::GetInstance()->SetTextBackgroundColor(21, RGB(192, 0, 0), currentHp);
			Renderer::GetInstance()->SetTextBackgroundColor(22, RGB(0, 0, 192), currentMp);
			Renderer::GetInstance()->SetTextBackgroundColor(23, RGB(0, 192, 0), currentExp);

			PrintBattleStatus();

			// 플레이어 차례
			Renderer::GetInstance()->EditObjectColor(61, RGB(0, 255, 255));
			Renderer::GetInstance()->EditObjectColor(62, RGB(128, 128, 128));

			if (battle->GetIsPlayerTurn())
			{
				isRun = battle->PlayerTurn(monsters[i]);
			}
			if (isRun)
			{
				break;
			}
			// 플레이어 턴 후의 몬스터 체력바 렌더링
			enemyHp = monsters[i]->GetHealth();
			if (enemyHp < 0) enemyHp = 0;
			currentEnemyHp = enemyHp * 80 / enemyMaxHp;

			Renderer::GetInstance()->EditText(51, format("{} / {}", enemyHp, enemyMaxHp));
			Renderer::GetInstance()->SetTextBackgroundColor(51, RGB(192, 0, 0), currentEnemyHp);

			//몬스터 차례
			Renderer::GetInstance()->EditObjectColor(61, RGB(128, 128, 128));
			Renderer::GetInstance()->EditObjectColor(62, RGB(0, 255, 255));
			// 몹이 죽었을 때 몹아이콘 색깔
			if (enemyHp <= 0)
			{
				Renderer::GetInstance()->EditObjectColor(62, RGB(64, 0, 64));
			}

			if (battle->GetIsMonsterTurn())
			{
				isMonsterDie = battle->MonsterTurn(monsters[i]);
			}
			
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