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

	LogBox::GetInstance()->Print("* �÷��̾� �� *");

	while (true)
	{
		LogBox::GetInstance()->Print("1. ���� / 2. ��ų / 3. ������ / 4. ����");
		if (character->IsDead())
		{
			LogBox::GetInstance()->Print("ĳ���Ͱ� ����Ͽ����ϴ�.������ ����˴ϴ�.",RGB(255,0,255));
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		LogBox::GetInstance()->Clear();
		choice = InputBox::GetInstance()->InputNumber();

		if (choice == 1)
		{
			LogBox::GetInstance()->Print(format("{} �� ����!", character->GetName()));
			int damage = character->CharacterAttack();
			monster->TakeDamage(damage);
			LogBox::GetInstance()->Print(format("{} �� {} �������� �Ծ����ϴ�.", monster->GetName(), damage));
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
			LogBox::GetInstance()->Print(format("{} �� {} �������� �Ծ����ϴ�.", monster->GetName(), skillDamage));
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
			LogBox::GetInstance()->Print("������ �����ϼ̽��ϴ�. ����ȭ������ ���ư��ϴ�.");
			Sleep(1500);
			return true;
		}
	}

	isMonsterTurn = true;	// �÷��̾� �ൿ������ ������
	isPlayerTurn = false;
	return false;
}

bool Battle::MonsterTurn(Monster* monster)
{
	if (monster->GetHealth() <= 0)
	{
		// ���� óġ�� ���Ͱ� �������� ��� ���� ����
		if (monster->IsBoss())
		{
			LogBox::GetInstance()->Print("******** �����մϴ�! ���� ������ ����Ͽ����ϴ�! ********",RGB(0,255,255));
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		monster->Die();
		Sleep(1500);

		int exp = monster->DropExp();
		int gold = monster->DropGold();
		LogBox::GetInstance()->Print(format("{} �� {} ����ġ�� ȹ���Ͽ����ϴ�!", character->GetName(), exp));
		LogBox::GetInstance()->Print(format("{} �� {} ��带 ȹ���Ͽ����ϴ�!", character->GetName(), gold));
		Sleep(1500);
		character->TakeExp(exp);
		character->TakeGold(gold);
		// ���� ������ ���ݷ� ��������
		character->SetAttackBonus(0);

		return true;
	}
	else
	{
		LogBox::GetInstance()->Print(format("{} �� ����!", monster->GetName()));
		Sleep(1500);
		character->TakeDamage(monster->MonsterAttack());
		Sleep(1500);
	}

	isMonsterTurn = false;	// ���� �ൿ������ �÷��̾���
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