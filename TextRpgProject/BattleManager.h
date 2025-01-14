#pragma once
#include <vector>
#include "Battle.h"
#include "SingleTon.h"

class BattleManager : public SingleTon<BattleManager>
{
private:
	Battle* battle;
	int battleLevel;

	friend class SingleTon<BattleManager>;
	BattleManager() = default;
	~BattleManager() = default;
public:
	void Init();
	void PrintBattleStatus();												// ������Ȳ ���
	void PrintBattleResult();												// ������� ���
	bool CreateBattle(int battleLevel, Character* character);				// ���� �÷��̾�, ���� ��ġ
	void StartBattle();														// ���� ����
	void EndBattle(const std::string& message);								// ���� ����

	int GetBattleLevel() const;
	void SetBattleLevel(int battleLevel);
};