#include "GameManager.h"

void GameManager::InitManager()
{
	playerManager = PlayerManager::GetInstance();
	factoryManager = FactoryManager::GetInstance();
	battleManager = BattleManager::GetInstance();
	tradeManager = TradeManager::GetInstance();
}

void GameManager::StartGame()
{
	InitManager();
	string a = "owo";
	playerManager->CreatePlayer();
	ProgressGame();
}

void GameManager::ProgressGame()
{
	while (true)
	{
		
	}
}

void GameManager::SelectOption()
{
}

void GameManager::EncounterEnemy()
{

}
