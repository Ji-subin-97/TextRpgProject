#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include "GameManager.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "BattleManager.h"
//렌더링 
#include "Renderer.h"
#include "GameMap.h"

using namespace std;

CharacterManager* characterManager;
BattleManager* battleManager;
SkillManager* skillManager;
static Character* curCharacter;
//렌더링 클래스 추가
Renderer* renderer;


void GameManager::Init()
{
	characterManager = CharacterManager::GetInstance();
	battleManager = BattleManager::GetInstance();
	skillManager = SkillManager::GetInstance();
	//렌더링 관리자
	renderer = Renderer::GetInstance();
	battleManager->Init();
}

void GameManager::CreateCharacter()
{
	/*
	cout << "----------------------------------------------" << endl;
	cout << "|                  TEXT RPG                  |" << endl;
	cout << "----------------------------------------------" << endl;
	*/

	renderer->SelectMap(GameMap::index());							// 캐릭터 생성화면
	characterManager->CreateCharacter();							// 캐릭터 생성
	curCharacter = characterManager->GetCharacter();				// 현재 캐릭터지정

	cout << "캐릭터 생성완료!" << endl;
	Sleep(2000);
}

bool GameManager::Main()
{
	system("cls");
	cout << "[ " << curCharacter->GetName() << " ] 님 어서오세요. 원하시는 행동을 선택해주세요!" << endl;
	characterManager->PrintCharacterInfoAll();

	int choice = 0;

	cout << "\n1. 전투" << endl;
	cout << "2. 인벤토리" << endl;
	cout << "3. 상점" << endl;
	cout << "4. 종료" << endl;

	cout << "\n행동 선택: ";
	cin >> choice;

	if (cin.fail())
	{
		cout << "숫자만 입력가능합니다." << endl;
		cin.clear();
		cin.ignore();

		return true;
	}

	switch (choice)
	{
	case 1:
		Battle();
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		cout << "게임을 종료합니다." << endl;
		return false;
		break;
	default:
		cout << "메뉴에 해당되는 번호만 입력해주세요." << endl;
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
		int choice;

		system("cls");
		characterManager->PrintCharacterInfoAll();
		cout << "현재 전투레벨: " << battleManager->GetBattleLevel() << " LV" << endl;

		cout << "\n1. 전투시작" << endl;
		cout << "2. 전투레벨설정" << endl;
		cout << "3. 메인화면" << endl;
		cout << "행동 선택: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "숫자만 입력가능합니다." << endl;
			cin.clear();
			cin.ignore();

			continue;
		}

		switch (choice)
		{
		case 1:
			isCreate = battleManager->CreateBattle(battleManager->GetBattleLevel(), curCharacter);
			if (isCreate)
			{
				battleManager->StartBattle();
			}
			else
			{
				cout << "전투레벨 생성에 실패하였습니다. 다시 시도해주세요." << endl;
			}
			break;
		case 2:
			while (true)
			{
				cin.ignore();
				cout << "원하시는 전투레벨을 입력해주세요. (1LV ~ 5LV)" << endl;
				cout << "입력: ";
				cin >> choice;

				if (cin.fail())
				{
					cout << "숫자만 입력가능합니다." << endl;
					cin.clear();
					cin.ignore();

					continue;
				}

				if (choice < 1 || choice > 5)
				{
					cout << "전투레벨은 1LV ~ 5LV까지만 입력가능합니다." << endl;
					continue;
				}
				else
				{
					battleManager->SetBattleLevel(choice);
					break;
				}
			}
			break;
		case 3:
			flag = false;
			break;
		default:
			cout << "메뉴에 해당되는 번호만 입력해주세요." << endl;
			continue;
			break;
		}
	}
}

