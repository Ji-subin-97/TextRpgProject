#include <iostream>
#include "Orc.h"
#include "Random.h"

using namespace std;

Orc::Orc(int playerLevel) {
	name = "��ũ";
	isBoss = false;

	int healthBase = GetIntToRandom(20, 30);
	int attackBase = GetIntToRandom(5, 7);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Orc::MonsterAttack()
{
	cout << "��ũ�� �Ŵ��� ����̷� �����ƴ�." << endl;

	return attack;
}

void Orc::TakeDamage(int attack)
{
	health -= attack;
}

int Orc::DropExp()
{
	return GetIntToRandom(60, 80);
}

int Orc::DropGold()
{
	return GetIntToRandom(50, 70);
}

void Orc::Die()
{
	cout << "��ũ�� ���̻� �Ҹ����� �ʴ´�." << endl;
}

bool Orc::IsBoss()
{
	return isBoss;
}

const string& Orc::GetName() const
{
	return name;
}

int Orc::GetHealth() const
{
	return health;
}

int Orc::GetAttack() const
{
	return attack;
}

void Orc::SetHealth(int health)
{
	this->health = health;
}

void Orc::SetAttack(int attack)
{
	this->attack = attack;
}