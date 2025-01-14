#include <iostream>
#include <Windows.h>
#include "Battle.h"

using namespace std;

bool Battle::PlayerTurn(Monster* monster)
{
	int choice = 0;

	cout << "\n* 플레이어 턴 *" << endl;
	cout << "1. 공격 ( " << character->GetAttack() << " )" << endl;
	cout << "2. 스킬" << endl;
	// cout << "2. 아이템" << endl;
	cout << "3. 도망" << endl;
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
	}
	else if (choice == 2)
	{
		cout << "==============================================" << endl;
		int skillDamage = character->UseSkill();
		monster->TakeDamage(skillDamage);
		cout << monster->GetName() << " 은 " << skillDamage << " 데미지를 입었습니다." << endl;
		Sleep(1500);
	}
	//else if (choice == 2)
	//{
	//	// 캐릭터 아이템 리스트 불러오고 선택해서 사용: 아이템사용도 턴 소모
	//	cout << "사용하실 아이템을 선택해주세요." << endl;
	//	character->CheckInventory();
	//	cout << "선택: ";
	//	cin >> choice;


	//}
	else if (choice == 3)
	{
		cout << "도망을 선택하셨습니다. 전투화면으로 돌아갑니다." << endl;
		Sleep(1500);
		return true;
	}

	return false;
}

bool Battle::MonsterTurn(Monster* monster)
{
	if (monster->GetHealth() <= 0)
	{
		int exp = monster->DropExp();
		cout << character->GetName() << "은 " << exp << " 경험치를 획득하였습니다!" << endl;
		Sleep(1500);
		character->TakeExp(exp);

		//Item* item = monster->DropItem(30);

		//if (item != nullptr)
		//{
		//	character->TakeItem(item);
		//}

		return true;
	}
	else
	{
		cout << monster->GetName() << " 의 공격!" << endl;
		Sleep(1500);
		character->TakeDamage(monster->GetAttack());
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