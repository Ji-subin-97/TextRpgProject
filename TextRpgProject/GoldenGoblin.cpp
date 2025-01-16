#include <iostream>
#include "GoldenGoblin.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

GoldenGoblin::GoldenGoblin(int playerLevel) {
	name = "황금 고블린";
	isBoss = true;

	int healthBase = 1000;
	int attackBase = 60;
	health = 1500;
	attack = 100;
}

int GoldenGoblin::MonsterAttack()
{
	LogBox::GetInstance()->Print("황금 고블린은 당신의 아이템을 노리고있다.");
	//cout << "황금 고블린은 당신의 아이템을 노리고있다. " << endl;

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
	LogBox::GetInstance()->Print("고블린은 더이상 심장이 뛰지 않는다.", RGB(255, 0, 255));
	//cout << "고블린은 더이상 심장이 뛰지 않는다." << endl;
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