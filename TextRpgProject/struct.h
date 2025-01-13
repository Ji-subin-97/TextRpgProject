#pragma once

// Pawn id
enum class PawnId : int
{
	HUMAN = 1,
	GOBLIN,
	ORC,
	TROLL,
	SLIME
};

// item id
enum class ItemId : int
{
	HEALTH_POTION,
	ATTACK_BOOST
};

// 레벨 1 기준 능력치
struct BaseAbility
{
	int maxHealth;
	int attack;
};