#include <iostream>
#include "Orc.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

Orc::Orc(int playerLevel) {
	name = "오크";
	isBoss = false;

	int healthBase = GetIntToRandom(30, 50);
	int attackBase = GetIntToRandom(5, 10);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Orc::MonsterAttack()
{
	LogBox::GetInstance()->Print("오크는 거대한 방망이로 내려쳤다.");
	//cout << "오크는 거대한 방망이로 내려쳤다." << endl;

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
	LogBox::GetInstance()->Print("오크는 더이상 소리내지 않는다.");
	//cout << "오크는 더이상 소리내지 않는다." << endl;
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