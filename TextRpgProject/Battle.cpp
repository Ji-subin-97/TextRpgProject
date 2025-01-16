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

	cout << "\n* �÷��̾� �� *" << endl;
	cout << "1. ���� ( " << character->GetAttack() << " + " <<  character->GetAttackBonus() << " )" << endl;
	cout << "2. ��ų" << endl;
	cout << "3. ������" << endl;
	cout << "4. ����" << endl;

	while (true)
	{
		if (character->IsDead())
		{
			cout << "ĳ���Ͱ� ����Ͽ����ϴ�. ������ ����˴ϴ�." << endl;
			Sleep(2000);
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		cout << "�ൿ�Է�: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "���ڸ� �Է°����մϴ�." << endl;
			cin.clear();
			cin.ignore();
		}

		if (choice == 1)
		{
			cout << "==============================================" << endl;
			cout << character->GetName() << " �� ����!" << endl;
			int damage = character->CharacterAttack();
			monster->TakeDamage(damage);
			cout << monster->GetName() << " �� " << damage << " �������� �Ծ����ϴ�." << endl;
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
			cout << monster->GetName() << " �� " << skillDamage << " �������� �Ծ����ϴ�." << endl;
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
			cout << "������ �����ϼ̽��ϴ�. ����ȭ������ ���ư��ϴ�." << endl;
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
			cout << "************************************************ �����մϴ�! ���� ������ ����Ͽ����ϴ�! ************************************************" << endl;
			Sleep(2000);
			cout << "������ ����˴ϴ�." << endl;
			GameManager::GetInstance()->EndGame();
			exit(0);
		}

		monster->Die();
		Sleep(1500);

		int exp = monster->DropExp();
		int gold = monster->DropGold();
		cout << character->GetName() << "�� " << exp << " ����ġ�� ȹ���Ͽ����ϴ�!" << endl;
		cout << character->GetName() << "�� " << gold << " ��带 ȹ���Ͽ����ϴ�!" << endl;
		Sleep(1500);
		character->TakeExp(exp);
		character->TakeGold(gold);
		// ���� ������ ���ݷ� ��������
		character->SetAttackBonus(0);

		return true;
	}
	else
	{
		cout << monster->GetName() << " �� ����!" << endl;
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