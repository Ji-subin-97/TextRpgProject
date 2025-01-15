#include <iostream>
#include <crtdbg.h>
#include "GameManager.h"
using namespace std;

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool isGameRun = true;		// 게임실행여부 확인용

	GameManager* gameManager = GameManager::GetInstance();

	// 초기세팅
	gameManager->Init();

	// 캐릭터 생성
	gameManager->CreateCharacter();

	// 메인화면
	while (isGameRun)
	{
		isGameRun = gameManager->Main();
	}

	return 0;
}