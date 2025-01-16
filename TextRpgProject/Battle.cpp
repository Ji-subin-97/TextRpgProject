#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "Battle.h"
#include "GameManager.h"

using namespace std;

bool Battle::PlayerTurn(Monster* monster)
{
	int choice = 0;

	cout << "\n* 플레이어 턴 *" << endl;
	cout << "1. 공격 ( " << character->GetAttack() << " + " <<  character->GetAttackBonus() << " )" << endl;
	cout << "2. 스킬" << endl;
	cout << "3. 아이템" << endl;
	cout << "4. 도망" << endl;

	while (true)
	{
		if (character->IsDead())
		{
			cout << "캐릭터가 사망하였습니다. 게임이 종료됩니다." << endl;
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		cout << "행동입력: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();
		}

		if (choice == 1)
		{
			cout << "==============================================" << endl;
			cout << character->GetName() << " 의 공격!" << endl;
			int damage = character->CharacterAttack();
			monster->TakeDamage(damage);
			cout << monster->GetName() << " 은 " << damage << " 데미지를 입었습니다." << endl;
			Sleep(1500);
			
			break;
		}
		else if (choice == 2)
		{
			int skillDamage = character->UseSkill();
			if (skillDamage == -1) {
				return false;
			} 

			cout << "==============================================" << endl;
			monster->TakeDamage(skillDamage);
			cout << monster->GetName() << " 은 " << skillDamage << " 데미지를 입었습니다." << endl;
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
			cout << "도망을 선택하셨습니다. 전투화면으로 돌아갑니다." << endl;
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
			cout << "************************************************ 축하합니다! 최종 보스를 토벌하였습니다! ************************************************" << endl;
			Sleep(2000);
			cout << "게임이 종료됩니다." << endl;
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		monster->Die();
		Sleep(1500);

		int exp = monster->DropExp();
		int gold = monster->DropGold();
		cout << character->GetName() << "은 " << exp << " 경험치를 획득하였습니다!" << endl;
		cout << character->GetName() << "은 " << gold << " 골드를 획득하였습니다!" << endl;
		Sleep(1500);
		character->TakeExp(exp);
		character->TakeGold(gold);
		// 전투 종료후 공격력 버프해제
		character->SetAttackBonus(0);

		return true;
	}
	else
	{
		cout << monster->GetName() << " 의 공격!" << endl;
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