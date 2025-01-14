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
	void PrintBattleStatus();												// 전투상황 출력
	void PrintBattleResult();												// 전투결과 출력
	bool CreateBattle(int battleLevel, Character* character);				// 전투 플레이어, 몬스터 배치
	void StartBattle();														// 전투 시작
	void EndBattle(const std::string& message);								// 전투 종료

	int GetBattleLevel() const;
	void SetBattleLevel(int battleLevel);
};