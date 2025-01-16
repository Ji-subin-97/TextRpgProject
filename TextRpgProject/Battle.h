#pragma once
#include "Character.h"
#include "Monster.h"

class Battle
{
private:
	Character* character;
	std::vector<Monster*> monsters;
	int battleLevel;
	bool isPlayerTurn;
	bool isMonsterTurn;
public:
	Battle(Character* character, std::vector<Monster*> monsters, int battleLevel)
		: character(character), monsters(monsters), battleLevel(battleLevel), isPlayerTurn(false), isMonsterTurn(false) {
	}
	~Battle()
	{
		for (Monster* monster : monsters)
		{
			delete monster;
		}

		monsters.clear();
		monsters.shrink_to_fit();
	}

	bool PlayerTurn(Monster* monster);
	bool MonsterTurn(Monster* monster);

	bool GetIsPlayerTurn() const;
	bool GetIsMonsterTurn() const;

	void SetIsPlayerTurn(bool b);
	void SetIsMonsterTurn(bool b);

	const Character* GetCharacter() const;
	const std::vector<Monster*>& GetMonsters() const;
};