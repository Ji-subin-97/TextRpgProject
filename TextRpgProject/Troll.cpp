#include <iostream>
#include "Troll.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

Troll::Troll(int playerLevel) {
	name = "Ʈ��";
	isBoss = false;

	int healthBase = GetIntToRandom(30, 40);
	int attackBase = GetIntToRandom(6, 8);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Troll::MonsterAttack()
{
	//cout << "�Ŵ��� �����̸� �̲��� �÷��̾ �������� �Ѵ�." << endl;
	LogBox::GetInstance()->Print("�Ŵ��� �����̸� �̲��� �÷��̾ �������� �Ѵ�.");

	return attack;
}

void Troll::TakeDamage(int attack)
{
	health -= attack;
}

int Troll::DropExp()
{
	return GetIntToRandom(80, 100);
}

int Troll::DropGold()
{
	return GetIntToRandom(70, 100);
}

void Troll::Die()
{
	LogBox::GetInstance()->Print("�Ŵ��� �����̴� ���̻� �������� �ʴ´�.", RGB(255, 0, 255));
	//cout << "�Ŵ��� �����̴� ���̻� �������� �ʴ´�." << endl;
}

bool Troll::IsBoss()
{
	return isBoss;
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