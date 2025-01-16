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

	/*
	cout << "\n* 플레이어 턴 *" << endl;
	cout << "1. 공격 ( " << character->GetAttack() << " )" << endl;
	cout << "2. 스킬" << endl;
	  // cout << "2. 아이템" << endl;
	cout << "3. 도망" << endl;
	*/
	LogBox::GetInstance()->Print("* 플레이어 턴 *");
	LogBox::GetInstance()->Print("1. 공격 / 2. 스킬 / 3. 도망");
	while (true)
	{
		if (character->IsDead())
		{
			//cout << "캐릭터가 사망하였습니다. 게임이 종료됩니다." << endl;
			LogBox::GetInstance()->Print("캐릭터가 사망하였습니다.게임이 종료됩니다.");
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		/*
		cout << "행동입력: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();
		}
		*/

		choice = InputBox::GetInstance()->InputNumber();

		if (choice == 1)
		{
			LogBox::GetInstance()->Print(format("{} 의 공격!", character->GetName()));
			/*
			cout << "==============================================" << endl;
			cout << character->GetName() << " 의 공격!" << endl;
			*/
			int damage = character->CharacterAttack();
			monster->TakeDamage(damage);
			//cout << monster->GetName() << " 은 " << damage << " 데미지를 입었습니다." << endl;
			LogBox::GetInstance()->Print(format("{} 은 {} 데미지를 입었습니다.", monster->GetName(), damage));
			Sleep(1500);
			
			break;
		}
		else if (choice == 2)
		{
			int skillDamage = character->UseSkill();

			if (skillDamage == -1)
			{
				continue;
			}

			//cout << "==============================================" << endl;
			monster->TakeDamage(skillDamage);
			//cout << monster->GetName() << " 은 " << skillDamage << " 데미지를 입었습니다." << endl;
			LogBox::GetInstance()->Print(format("{} 은 {} 데미지를 입었습니다.", monster->GetName(), skillDamage));

			Sleep(1500);

			break;
		}
		// 캐릭터 아이템 리스트 불러오고 선택해서 사용: 아이템사용도 턴 소모
		else if (choice == 3)
		{
			LogBox::GetInstance()->Print("도망을 선택하셨습니다. 전투화면으로 돌아갑니다.");
			//cout << "도망을 선택하셨습니다. 전투화면으로 돌아갑니다." << endl;
			Sleep(1500);
			return true;
		}
	}

	return false;
}

bool Battle::MonsterTurn(Monster* monster)
{
	if (monster->GetHealth() <= 0)
	{
		// 만약 처치한 몬스터가 보스몹일 경우 게임 종료
		if (monster->IsBoss())
		{
			LogBox::GetInstance()->Print("**** 축하합니다! 최종 보스를 토벌하였습니다! ****");

			//cout << "************************************************ 축하합니다! 최종 보스를 토벌하였습니다! ************************************************" << endl;
			Sleep(2000);
			//cout << "게임이 종료됩니다." << endl;
			LogBox::GetInstance()->Print("게임이 종료됩니다.");
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		monster->Die();
		Sleep(1500);

		int exp = monster->DropExp();
		int gold = monster->DropGold();
		LogBox::GetInstance()->Print(format("{} 은 {} 경험치를 획득하였습니다!", character->GetName(), exp));
		LogBox::GetInstance()->Print(format("{} 은 {} 골드를 획득하였습니다!", character->GetName(), gold));
		//cout << character->GetName() << "은 " << exp << " 경험치를 획득하였습니다!" << endl;
		//cout << character->GetName() << "은 " << gold << " 골드를 획득하였습니다!" << endl;
		Sleep(1500);
		character->TakeExp(exp);
		character->TakeGold(gold);
		//Item* item = monster->DropItem(30);

		//if (item != nullptr)
		//{
		//	character->TakeItem(item);
		//}

		return true;
	}
	else
	{
		LogBox::GetInstance()->Print(format("{} 의 공격!", monster->GetName()));
		//cout << monster->GetName() << " 의 공격!" << endl;
		Sleep(1500);
		character->TakeDamage(monster->MonsterAttack());
		Sleep(1500);
	}

	return false;
}

const Character* Battle::GetCharacter() const
{
	return character;
}

const vector<Monster*>& Battle::GetMonsters() const
{
	return monsters;
}