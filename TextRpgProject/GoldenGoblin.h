#pragma once
#include "Monster.h"

class GoldenGoblin : public Monster
{
private:
	std::string name;
	int health;
	int attack;
public:
	GoldenGoblin(int playerLevel);
	~GoldenGoblin() {}

	int MonsterAttack() override;
	void TakeDamage(int attack) override;
	int DropExp() override;
	int DropGold() override;
	void Die() override;

	bool IsBoss() override;

	const std::string& GetName() const override;
	int GetHealth() const override;
	int GetAttack() const override;
	void SetHealth(int health) override;
	void SetAttack(int attack) override;
};