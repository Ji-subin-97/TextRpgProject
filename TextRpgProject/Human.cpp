#include <iostream>
#include "Human.h"
#include "Random.h"
#include "LogBox.h"

using namespace std;

Human::Human(int playerLevel) {
	name = "�ΰ�";
	isBoss = false;

	int healthBase = GetIntToRandom(40, 50);
	int attackBase = GetIntToRandom(9, 11);
	health = playerLevel * healthBase;
	attack = playerLevel * attackBase;
}

int Human::MonsterAttack()
{
	LogBox::GetInstance()->Print("���� �ֵθ��� �����ߴ�.");
	//cout << "���� �ֵθ��� �����ߴ�." << endl;

	return attack;
}

void Human::TakeDamage(int attack)
{
	health -= attack;
}

int Human::DropExp()
{
	return GetIntToRandom(100, 150);
}

int Human::DropGold()
{
	return GetIntToRandom(100, 150);
}

void Human::Die()
{
	LogBox::GetInstance()->Print("�״� �׾���.");
	//cout << "�״� �׾���." << endl;
}

bool Human::IsBoss()
{
	return isBoss;
}

const string& Human::GetName() const
{
	return name;
}

int Human::GetHealth() const
{
	return health;
}

int Human::GetAttack() const
{
	return attack;
}

void Human::SetHealth(int health)
{
	this->health = health;
}

void Human::SetAttack(int attack)
{
	this->attack = attack;
}