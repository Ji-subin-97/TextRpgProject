#include "Pawn.h"

void Pawn::SetLevel(int _level)
{
	this->level = _level;
}

int Pawn::GetLevel() const
{
	return this->level;
}

void Pawn::SetHealth(int _health)
{
	this->health = _health;
}

int Pawn::GetHealth() const
{
	return this->health;
}

void Pawn::SetAttack(int _attack)
{
	this->attack = _attack;
}

int Pawn::GetAttack() const
{
	return this->attack;
}
