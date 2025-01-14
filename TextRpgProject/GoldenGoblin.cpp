#include <iostream>
#include "GoldenGoblin.h"
#include "Random.h"

using namespace std;

GoldenGoblin::GoldenGoblin(int playerLevel) {
	name = "Ȳ�� ���";
	isBoss = true;

	int healthBase = 1000;
	int attackBase = 60;
	health = 1500;
	attack = 100;
}

int GoldenGoblin::MonsterAttack()
{
	cout << "Ȳ�� ����� ����� �������� �븮���ִ�. " << endl;

	return attack;
}

void GoldenGoblin::TakeDamage(int attack)
{
	health -= attack;
}

int GoldenGoblin::DropExp()
{
	return 200;
}

int GoldenGoblin::DropGold()
{
	return 500;
}

void GoldenGoblin::Die()
{
	cout << "����� ���̻� ������ ���� �ʴ´�." << endl;
}

bool GoldenGoblin::IsBoss()
{
	return isBoss;
}

const string& GoldenGoblin::GetName() const
{
	return name;
}

int GoldenGoblin::GetHealth() const
{
	return health;
}

int GoldenGoblin::GetAttack() const
{
	return attack;
}

void GoldenGoblin::SetHealth(int health)
{
	this->health = health;
}

void GoldenGoblin::SetAttack(int attack)
{
	this->attack = attack;
}