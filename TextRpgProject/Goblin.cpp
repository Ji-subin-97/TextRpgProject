#include <iostream>
#include "Goblin.h"
#include "Random.h"

using namespace std;

Goblin::Goblin(int playerLevel) {
	name = "���";

	int healthBase = GetIntToRandom(20, 30);
	int attackBase = GetIntToRandom(3, 5);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Goblin::MonsterAttack()
{
	cout << "����� �����ؿԴ�." << endl;

	return attack;
}

void Goblin::TakeDamage(int attack)
{
	health -= attack;
}

int Goblin::DropExp()
{
	return GetIntToRandom(10, 15);
}

int Goblin::DropGold()
{
	return GetIntToRandom(30, 50);
}

void Goblin::Die()
{
	cout << "����� ���̻� ������ ���� �ʴ´�." << endl;
}

const string& Goblin::GetName() const
{
	return name;
}

int Goblin::GetHealth() const
{
	return health;
}

int Goblin::GetAttack() const
{
	return attack;
}

void Goblin::SetHealth(int health)
{
	this->health = health;
}

void Goblin::SetAttack(int attack)
{
	this->attack = attack;
}