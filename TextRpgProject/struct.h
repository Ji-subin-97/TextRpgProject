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

// ���� 1 ���� �ɷ�ġ
struct BaseAbility
{
	int maxHealth;
	int attack;
};