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
//렌더링 
#include "Renderer.h"
#include "GameMap.h"
#include "LogBox.h"
#include "Cursor.h"

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

	renderer->SelectMap(GameMap::Index());							// 캐릭터 생성화면
	characterManager->CreateCharacter();							// 캐릭터 생성
	curCharacter = characterManager->GetCharacter();				// 현재 캐릭터지정

	LogBox::GetInstance()->Print("캐릭터 생성완료!");
	//cout << "캐릭터 생성완료!" << endl;
	Sleep(2000);
}

bool GameManager::Main()
{
	//system("cls");
	renderer->SelectMap(GameMap::Main());
	LogBox::GetInstance()->Print(format("{} 님 어서오세요. 원하시는 행동을 선택해주세요!", curCharacter->GetName()));
	//cout << "[ " << curCharacter->GetName() << " ] 님 어서오세요. 원하시는 행동을 선택해주세요!" << endl;
	//characterManager->PrintCharacterInfoAll();

	int choice = 0;

	LogBox::GetInstance()->Print("1. 전투 / 2. 스텟관리 / 3. 인벤토리 / 4. 상점 / 5. 종료");

	choice = InputBox::GetInstance()->InputNumber();

	/*
	cout << "\n1. 전투" << endl;
	cout << "2. 캐릭터 스텟관리" << endl;
	cout << "3. 인벤토리" << endl;
	cout << "4. 상점" << endl;
	cout << "5. 종료" << endl;

	cout << "\n행동 선택: ";
	cin >> choice;

	if (cin.fail())
	{
		cout << "숫자만 입력가능합니다." << endl;
		cin.clear();
		cin.ignore();

		return true;
	}
	*/

	switch (choice)
	{
	case 1:
		Battle();
		break;
	case 2:
		characterManager->SetCharacterStat();
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		EndGame();
		return false;
		break;
	default:
		//cout << "메뉴에 해당되는 번호만 입력해주세요." << endl;
		LogBox::GetInstance()->Clear();
		LogBox::GetInstance()->Print("메뉴에 해당되는 번호만 입력해주세요.", RGB(255, 0, 0));
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

		/*
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
		*/
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
		Renderer::GetInstance()->EditText(33, stat["accuracy"] + " %");
		Renderer::GetInstance()->EditText(34, stat["skillEnhancement"] + " %");
		Renderer::GetInstance()->EditText(35, stat["criticalChance"] + " %");
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
				//cout << "전투레벨 생성에 실패하였습니다. 다시 시도해주세요." << endl;
			}
			break;
		case 2:
			LogBox::GetInstance()->Clear();

			while (true)
			{
				/*
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
				*/
				LogBox::GetInstance()->Print("원하시는 전투레벨을 입력해주세요. (1LV ~ 5LV)");
				choice = InputBox::GetInstance()->InputNumber();

				if (choice < 1 || choice > 5)
				{
					//cout << "전투레벨은 1LV ~ 5LV까지만 입력가능합니다." << endl;
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
			//cout << "메뉴에 해당되는 번호만 입력해주세요." << endl;
			LogBox::GetInstance()->Clear();
			LogBox::GetInstance()->Print("메뉴에 해당되는 번호만 입력해주세요.", RGB(255, 0, 0));
			continue;
			break;
		}
	}
}

void GameManager::EndGame()
{
	//cout << "게임을 종료합니다." << endl;
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

