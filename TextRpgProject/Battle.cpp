#include <iostream>
#include <Windows.h>
#include "Battle.h"

using namespace std;

bool Battle::PlayerTurn(Monster* monster)
{
	int choice = 0;

	cout << "\n* �÷��̾� �� *" << endl;
	cout << "1. ���� ( " << character->GetAttack() << " )" << endl;
	cout << "2. ��ų" << endl;
	// cout << "2. ������" << endl;
	cout << "3. ����" << endl;
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
	}
	else if (choice == 2)
	{
		cout << "==============================================" << endl;
		int skillDamage = character->UseSkill();
		monster->TakeDamage(skillDamage);
		cout << monster->GetName() << " �� " << skillDamage << " �������� �Ծ����ϴ�." << endl;
		Sleep(1500);
	}
	//else if (choice == 2)
	//{
	//	// ĳ���� ������ ����Ʈ �ҷ����� �����ؼ� ���: �����ۻ�뵵 �� �Ҹ�
	//	cout << "����Ͻ� �������� �������ּ���." << endl;
	//	character->CheckInventory();
	//	cout << "����: ";
	//	cin >> choice;


	//}
	else if (choice == 3)
	{
		cout << "������ �����ϼ̽��ϴ�. ����ȭ������ ���ư��ϴ�." << endl;
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
		cout << character->GetName() << "�� " << exp << " ����ġ�� ȹ���Ͽ����ϴ�!" << endl;
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
		cout << monster->GetName() << " �� ����!" << endl;
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