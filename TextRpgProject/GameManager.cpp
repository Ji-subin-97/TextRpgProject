#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <format>
#include <unordered_map>
#include "GameManager.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "BattleManager.h"
#include "ItemManager.h"
#include "ShopManager.h"
//렌더링 
#include "Renderer.h"
#include "GameMap.h"
#include "LogBox.h"
#include "Cursor.h"

using namespace std;

CharacterManager* characterManager;
BattleManager* battleManager;
SkillManager* skillManager;
ItemManager* itemManager;
ShopManager* shopManager;
static Character* curCharacter;
//렌더링 클래스 추가
Renderer* renderer;


void GameManager::Init()
{
	characterManager = CharacterManager::GetInstance();
	battleManager = BattleManager::GetInstance();
	skillManager = SkillManager::GetInstance();
	itemManager = ItemManager::GetInstance();
	shopManager = ShopManager::GetInstance();
	//렌더링 관리자
	renderer = Renderer::GetInstance();
	battleManager->Init();
}

void GameManager::CreateCharacter()
{
	renderer->SelectMap(GameMap::Index());							// 캐릭터 생성화면
	characterManager->CreateCharacter();							// 캐릭터 생성
	curCharacter = characterManager->GetCharacter();				// 현재 캐릭터지정

	LogBox::GetInstance()->Print("캐릭터 생성완료!");
	Sleep(1000);
}

bool GameManager::Main()
{
	renderer->SelectMap(GameMap::Main());
	LogBox::GetInstance()->Print(format("{} 님 어서오세요. 원하시는 행동을 선택해주세요!", curCharacter->GetName()));

	int choice = 0;

	LogBox::GetInstance()->Print("1. 전투 / 2. 스텟관리 / 3. 인벤토리 / 4. 상점 / 5. 종료");

	choice = InputBox::GetInstance()->InputNumber();

	switch (choice)
	{
	case 1:
		Battle();
		break;
	case 2:
		characterManager->SetCharacterStat();
		break;
	case 3:
		LogBox::GetInstance()->Clear();
		curCharacter->PrintItemList();
		Sleep(3000);
		break;
	case 4:
		Cursor::ClearScreen();
		shopManager->VisitShop(*curCharacter);
		break;
	case 5:
		EndGame();
		return false;
		break;
	default:
		LogBox::GetInstance()->Print("메뉴에 해당되는 번호만 입력해주세요.", RGB(255, 0, 0));
		Sleep(500);
		return true;
		break;
	}

	return true;
}

void GameManager::Battle()
{
	bool flag = true;
	bool isCreate = false;


	while (flag)
	{
	renderer->SelectMap(GameMap::SelectBattle());
		

		int choice;

		unordered_map<string, string> stat = characterManager->GetCharacterStat();

		Renderer::GetInstance()->EditText(21, stat["level"]);
		Renderer::GetInstance()->EditText(22, stat["hp"]);
		Renderer::GetInstance()->EditText(23, stat["mp"]);
		Renderer::GetInstance()->EditText(24, stat["str"]);
		Renderer::GetInstance()->EditText(25, stat["dex"]);
		Renderer::GetInstance()->EditText(26, stat["int"]);
		Renderer::GetInstance()->EditText(27, stat["luk"]);
		Renderer::GetInstance()->EditText(31, stat["attack"]);
		Renderer::GetInstance()->EditText(32, stat["damageReduction"]);
		Renderer::GetInstance()->EditText(33, "  " + stat["accuracy"] + " %");
		Renderer::GetInstance()->EditText(34, "  " + stat["skillEnhancement"] + " %");
		Renderer::GetInstance()->EditText(35, "  " + stat["criticalChance"] + " %");
		Renderer::GetInstance()->EditText(36, stat["exp"]);
		Renderer::GetInstance()->EditText(37, stat["gold"]);
		Renderer::GetInstance()->EditText(40, stat["name"]);
		Renderer::GetInstance()->ExpandText(40, 1, 0);


		int hp = stoi(stat["hp"]);
		int mp = stoi(stat["mp"]);
		int exp = stoi(stat["exp"]);
		int maxHp = stoi(stat["maxHp"]);
		int maxMp = stoi(stat["maxMp"]);
		int maxExp = stoi(stat["maxExp"]);
		int currentHp = hp * 50 / maxHp;
		int currentMp = mp * 50 / maxMp;
		int currentExp = exp * 50 / maxExp;

		Renderer::GetInstance()->EditText(51, format("{} / {}", hp, maxHp));
		Renderer::GetInstance()->EditText(52, format("{} / {}", mp, maxMp));
		Renderer::GetInstance()->EditText(53, format("{} / {}", exp, maxExp));

		Renderer::GetInstance()->SetTextBackgroundColor(51, RGB(192, 0, 0), currentHp);
		Renderer::GetInstance()->SetTextBackgroundColor(52, RGB(0, 0, 192), currentMp);
		Renderer::GetInstance()->SetTextBackgroundColor(53, RGB(0, 192, 0), currentExp);

		LogBox::GetInstance()->Print("1. 전투시작 / 2. 전투레벨설정 / 3. 메인화면");
		LogBox::GetInstance()->Print(format("현재 전투레벨은 {} 입니다.", battleManager->GetBattleLevel()));

		choice = InputBox::GetInstance()->InputNumber();

		switch (choice)
		{
		case 1:
			isCreate = battleManager->CreateBattle(battleManager->GetBattleLevel(), curCharacter);
			if (isCreate)
			{
				LogBox::GetInstance()->Clear();
				battleManager->StartBattle();
			}
			else
			{
				LogBox::GetInstance()->Clear();
				LogBox::GetInstance()->Print("전투레벨 생성에 실패하였습니다. 다시 시도해주세요.", RGB(255, 0, 0));
			}
			break;
		case 2:
			LogBox::GetInstance()->Clear();

			while (true)
			{
				LogBox::GetInstance()->Print("원하시는 전투레벨을 입력해주세요. (1LV ~ 5LV)");
				choice = InputBox::GetInstance()->InputNumber();

				if (choice < 1 || choice > 5)
				{
					LogBox::GetInstance()->Clear();
					LogBox::GetInstance()->Print("전투레벨은 1LV ~5LV까지만 입력가능합니다.", RGB(255, 0, 0));
					continue;
				}
				else
				{
					LogBox::GetInstance()->Clear();
					battleManager->SetBattleLevel(choice);
					break;
				}
			}
			break;
		case 3:
			flag = false;
			break;
		default:
			LogBox::GetInstance()->Clear();
			LogBox::GetInstance()->Print("메뉴에 해당되는 번호만 입력해주세요.", RGB(255, 0, 0));
			continue;
			break;
		}
	}
}

void GameManager::EndGame()
{
	LogBox::GetInstance()->Print("게임을 종료합니다.", RGB(255, 0, 255));
	Sleep(2000);
	renderer->ClearAll();
	Cursor::SetTextColor(ForeColor::White);
	
	renderer->DeleteInstanceAll();
	skillManager->DeleteInstance();
	characterManager->DeleteInstance();
	battleManager->DeleteInstance();
	this->DeleteInstance();
}

