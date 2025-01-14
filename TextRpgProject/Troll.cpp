#include <iostream>
#include "Troll.h"
#include "Random.h"

using namespace std;

Troll::Troll(int playerLevel) {
	name = "Ʈ��";

	int healthBase = GetIntToRandom(50, 60);
	int attackBase = GetIntToRandom(15, 20);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Troll::MonsterAttack()
{
	cout << "�Ŵ��� �����̸� �̲��� �÷��̾ �������� �Ѵ�." << endl;

	return attack;
}

void Troll::TakeDamage(int attack)
{
	health -= attack;
}

int Troll::DropExp()
{
	return GetIntToRandom(30, 50);
}

int Troll::DropGold()
{
	return GetIntToRandom(70, 100);
}

void Troll::Die()
{
	cout << "�Ŵ��� �����̴� ���̻� �������� �ʴ´�." << endl;
}

const string& Troll::GetName() const
{
	return name;
}

int Troll::GetHealth() const
{
	return health;
}

int Troll::GetAttack() const
{
	return attack;
}

void Troll::SetHealth(int health)
{
	this->health = health;
}

void Troll::SetAttack(int attack)
{
	this->attack = attack;
}