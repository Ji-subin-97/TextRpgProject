#include <iostream>
#include <Windows.h>
#include "Battle.h"
#include "GameManager.h"

using namespace std;

bool Battle::PlayerTurn(Monster* monster)
{
	int choice = 0;

	cout << "\n* �÷��̾� �� *" << endl;
	cout << "1. ���� ( " << character->GetAttack() << " )" << endl;
	cout << "2. ��ų" << endl;
	// cout << "2. ������" << endl;
	cout << "3. ����" << endl;

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

			if (skillDamage == -1)
			{
				continue;
			}

			cout << "==============================================" << endl;
			monster->TakeDamage(skillDamage);
			cout << monster->GetName() << " �� " << skillDamage << " �������� �Ծ����ϴ�." << endl;
			Sleep(1500);

			break;
		}
		// ĳ���� ������ ����Ʈ �ҷ����� �����ؼ� ���: �����ۻ�뵵 �� �Ҹ�
		else if (choice == 3)
		{
			cout << "������ �����ϼ̽��ϴ�. ����ȭ������ ���ư��ϴ�." << endl;
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
		//Item* item = monster->DropItem(30);

		//if (item != nullptr)
		//{
		//	character->TakeItem(item);
		//}

		return true;
	}
	else
	{
		cout << monster->GetName() << " �� ����!" << endl;
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