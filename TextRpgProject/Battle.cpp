#include <iostream>
#include <format>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Battle.h"
#include "GameManager.h"
#include "InputBox.h"
#include "LogBox.h"

using namespace std;

bool Battle::PlayerTurn(Monster* monster)
{
	int choice = 0;

	LogBox::GetInstance()->Print("* 플레이어 턴 *");

	while (true)
	{
		LogBox::GetInstance()->Print("1. 공격 / 2. 스킬 / 3. 아이템 / 4. 도망");
		if (character->IsDead())
		{
			LogBox::GetInstance()->Print("캐릭터가 사망하였습니다.게임이 종료됩니다.",RGB(255,0,255));
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		LogBox::GetInstance()->Clear();
		choice = InputBox::GetInstance()->InputNumber();

		if (choice == 1)
		{
			LogBox::GetInstance()->Print(format("{} 의 공격!", character->GetName()));
			int damage = character->CharacterAttack();
			monster->TakeDamage(damage);
			LogBox::GetInstance()->Print(format("{} 은 {} 데미지를 입었습니다.", monster->GetName(), damage));
			Sleep(1500);
			
			break;
		}
		else if (choice == 2)
		{
			int skillDamage = character->UseSkill();
			if (skillDamage == -1) {
				return false;
			} 

			monster->TakeDamage(skillDamage);
			LogBox::GetInstance()->Print(format("{} 은 {} 데미지를 입었습니다.", monster->GetName(), skillDamage));
			Sleep(1500);

			break;
		}
		else if (choice == 3)
		{
			int itemUse = character->UseItem();
			if (itemUse == -1) {
				return false;
			}

			break;
		}
		else if (choice == 4)
		{
			LogBox::GetInstance()->Print("도망을 선택하셨습니다. 전투화면으로 돌아갑니다.");
			Sleep(1500);
			return true;
		}
	}

	isMonsterTurn = true;	// 플레이어 행동끝나면 몬스터턴
	isPlayerTurn = false;
	return false;
}

bool Battle::MonsterTurn(Monster* monster)
{
	if (monster->GetHealth() <= 0)
	{
		// 만약 처치한 몬스터가 보스몹일 경우 게임 종료
		if (monster->IsBoss())
		{
			LogBox::GetInstance()->Print("******** 축하합니다! 최종 보스를 토벌하였습니다! ********",RGB(0,255,255));
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		monster->Die();
		Sleep(1500);

		int exp = monster->DropExp();
		int gold = monster->DropGold();
		LogBox::GetInstance()->Print(format("{} 은 {} 경험치를 획득하였습니다!", character->GetName(), exp));
		LogBox::GetInstance()->Print(format("{} 은 {} 골드를 획득하였습니다!", character->GetName(), gold));
		Sleep(1500);
		character->TakeExp(exp);
		character->TakeGold(gold);
		// 전투 종료후 공격력 버프해제
		character->SetAttackBonus(0);

		return true;
	}
	else
	{
		LogBox::GetInstance()->Print(format("{} 의 공격!", monster->GetName()));
		Sleep(1500);
		character->TakeDamage(monster->MonsterAttack());
		Sleep(1500);
	}

	isMonsterTurn = false;	// 몬스터 행동끝나면 플레이어턴
	isPlayerTurn = true;

	return false;
}

bool Battle::GetIsPlayerTurn() const
{
	return isPlayerTurn;
}

bool Battle::GetIsMonsterTurn() const
{
	return isMonsterTurn;
}

void Battle::SetIsPlayerTurn(bool b)
{
	isPlayerTurn = b;
}

void Battle::SetIsMonsterTurn(bool b)
{
	isMonsterTurn = b;
}

const Character* Battle::GetCharacter() const
{
	return character;
}

const vector<Monster*>& Battle::GetMonsters() const
{
	return monsters;
}