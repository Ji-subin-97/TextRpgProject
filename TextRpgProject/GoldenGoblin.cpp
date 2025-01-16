#include <iostream>
#include "GoldenGoblin.h"
#include "Random.h"
#include "LogBox.h"

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
	LogBox::GetInstance()->Print("Ȳ�� ����� ����� �������� �븮���ִ�.");
	//cout << "Ȳ�� ����� ����� �������� �븮���ִ�. " << endl;

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
	LogBox::GetInstance()->Print("����� ���̻� ������ ���� �ʴ´�.", RGB(255, 0, 255));
	//cout << "����� ���̻� ������ ���� �ʴ´�." << endl;
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