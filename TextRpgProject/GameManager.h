#pragma once
#include "SingleTon.h"

class GameManager : public SingleTon<GameManager>
{
private:
	GameManager() = default;
	~GameManager() = default;
	friend class SingleTon<GameManager>;
public:
	void Init();					// 게임 초기세팅
	void CreateCharacter();			// 플레이어 생성
	bool Main();					// 메인화면
	void Battle();					// 전투화면
};