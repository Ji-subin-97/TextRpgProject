#include <iostream>
#include <crtdbg.h>
#include "GameManager.h"
using namespace std;

int main()
{
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	bool isGameRun = true;		// ���ӽ��࿩�� Ȯ�ο�

	GameManager* gameManager = GameManager::GetInstance();

	// �ʱ⼼��
	gameManager->Init();

	// ĳ���� ����
	gameManager->CreateCharacter();

	// ����ȭ��
	while (isGameRun)
	{
		isGameRun = gameManager->Main();
	}

	return 0;
}