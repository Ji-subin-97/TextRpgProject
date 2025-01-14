#include <iostream>
#include "Troll.h"
#include "Random.h"

using namespace std;

Troll::Troll(int playerLevel) {
	name = "트롤";

	int healthBase = GetIntToRandom(50, 60);
	int attackBase = GetIntToRandom(15, 20);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Troll::MonsterAttack()
{
	cout << "거대한 몽둥이를 이끌고 플레이어를 짓밟으려 한다." << endl;

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
	cout << "거대한 몸뚱이는 더이상 움직이지 않는다." << endl;
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