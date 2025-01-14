#pragma once
#include "Character.h"
#include "Monster.h"

class Battle
{
private:
	Character* character;
	std::vector<Monster*> monsters;
	int battleLevel;
public:
	Battle(Character* character, std::vector<Monster*> monsters, int battleLevel)
		: character(character), monsters(monsters), battleLevel(battleLevel) {
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

	const Character* GetCharacter() const;
	const std::vector<Monster*>& GetMonsters() const;
};