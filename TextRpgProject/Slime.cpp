#include <iostream>
#include "Slime.h"
#include "Random.h"

using namespace std;

Slime::Slime(int playerLevel) {
	name = "������";
	isBoss = false;

	int healthBase = GetIntToRandom(5, 10);
	int attackBase = GetIntToRandom(1, 3);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}
 
int Slime::MonsterAttack()
{
	cout << "�������� �ⷷ�Ÿ��� �����ߴ�." << endl;

	return attack;
}

void Slime::TakeDamage(int attack)
{
	health -= attack;
}

int Slime::DropExp()
{
	return GetIntToRandom(30, 35);
}

int Slime::DropGold()
{
	return GetIntToRandom(10, 20);
}

void Slime::Die()
{
	cout << "�������� ��ƹ��ȴ�." << endl;
}

bool Slime::IsBoss()
{
	return isBoss;
}

const string& Slime::GetName() const
{
	return name;
}

int Slime::GetHealth() const
{
	return health;
}

int Slime::GetAttack() const
{
	return attack;
}

void Slime::SetHealth(int health)
{
	this->health = health;
}

void Slime::SetAttack(int attack)
{
	this->attack = attack;
}