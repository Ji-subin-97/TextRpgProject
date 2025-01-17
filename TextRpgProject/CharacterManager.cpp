#include <iostream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <algorithm>
#include <string>
#include <format>
#include "CharacterManager.h"
#include "Random.h"
#include "LogBox.h"
#include "InputBox.h"
#include "Renderer.h"
#include "GameMap.h"
#include "Cursor.h"

using namespace std;

void CharacterManager::CreateCharacter()
{
	bool isComplete = false;
	Character* character = Character::GetInstance();

	if (character != nullptr)
	{
		character->Init();				// 캐릭터 초기화
		CreateRandomStat(*character);	// 처음 스텟 랜덤설정

		string name = "";
		LogBox::GetInstance()->Print("어서오세요. 캐릭터 생성에 앞서 이름을 정해주세요.");
		name = InputBox::GetInstance()->Input();

		character->SetName(name);

		Renderer::GetInstance()->SelectMap((GameMap::SelectStat()));
		//Sleep(500);
		LogBox::GetInstance()->Print(format("생성하신 플레이어의 이름은 {} 입니다.", name));
		Renderer::GetInstance()->EditText(20, name);
		Renderer::GetInstance()->ExpandText(20, 1, 0);
		Sleep(1000);


		while (!isComplete)
		{
			int choice = 0;

			LogBox::GetInstance()->Print("캐릭터의 기본 스텟을 정해주세요.");
			LogBox::GetInstance()->Print("플레이어 스텟이 마음에 드시면 완료, 아니면 재설정을 선택해주세요.");
			LogBox::GetInstance()->Print("1. 완료");
			LogBox::GetInstance()->Print("2. 재설정");
			// 첫번째 인수 : 오브젝트 ID, 두번째 인수 : 새로 렌더링할 텍스트
			Renderer::GetInstance()->EditText(11, character->GetCharacterStat().HP);
			Renderer::GetInstance()->EditText(12, character->GetCharacterStat().MP);
			Renderer::GetInstance()->EditText(13, character->GetCharacterStat().STR);
			Renderer::GetInstance()->EditText(14, character->GetCharacterStat().DEX);
			Renderer::GetInstance()->EditText(15, character->GetCharacterStat().INT);
			Renderer::GetInstance()->EditText(16, character->GetCharacterStat().LUK);

			choice = InputBox::GetInstance()->InputNumber();

			if (choice == 1)
			{
				LogBox::GetInstance()->Print("캐릭터 설정이 완료되었습니다. 캐릭터를 생성합니다.");
				Sleep(2000);
				isComplete = true;
			}
			else if (choice == 2)
			{
				LogBox::GetInstance()->Clear();
				CreateRandomStat(*character);
			}
			else
			{
				LogBox::GetInstance()->Clear();
				LogBox::GetInstance()->Print("잘못된 입력입니다.", RGB(255, 0, 0));
				continue;
			}

		}

		// 처음 설정된 기본스텟에 따른 캐릭터 세부 스텟 결정
		GenerateCharacter(*character, true);
	}
	else
	{
		LogBox::GetInstance()->Print("캐릭터 생성에 실패하였습니다. 관리자에게 문의해주세요.", RGB(255, 0, 0));
	}

}

Character* CharacterManager::GetCharacter()
{
	Character* character = Character::GetInstance();

	if (character == nullptr)
	{
		LogBox::GetInstance()->Print("캐릭터가 존재하지않습니다.", RGB(255, 0, 0));
	}

	return character;
}

void CharacterManager::CreateRandomStat(Character& character)
{
	// 캐릭터 스텟은 1 ~ 10 입니다.
	CharacterStat stat = character.GetCharacterStat();
	stat.HP = GetIntToRandom(1, 10);
	stat.MP = GetIntToRandom(1, 10);
	stat.STR = GetIntToRandom(1, 10);
	stat.DEX = GetIntToRandom(1, 10);
	stat.INT = GetIntToRandom(1, 10);
	stat.LUK = GetIntToRandom(1, 10);

	character.SetCharacterStat(stat);
}

void CharacterManager::GenerateCharacter(Character& character, bool isFirst)
{
	/* 계산공식
	*  체력 및 최대체력: 기본100 + (HP * 캐릭터레벨 * 10)
	   마나 및 최대마나: 기본50 + (MP * 캐릭터레벨 * 5)
	   공격력: 기본10 + ( (STR, DEX, LUK중 높은거) + 캐릭터레벨 * 5)
	   
	   피해감소율: STR++
	   명중률 : 기본 50.0 + DEX++
	   스킬강화 : INT * 5
	   치명타: LUK * 2
	*/
	int charLevel = character.GetLevel();

	int HP = 100 + (character.GetCharacterStat().HP * charLevel * 10);
	int MP = 50 + (character.GetCharacterStat().MP * charLevel * 5);
	int ATTACK = 10 + 
		(std::max({ character.GetCharacterStat().STR
			, character.GetCharacterStat().DEX
			, character.GetCharacterStat().LUK }) + charLevel * 5);

	if (isFirst)
	{
		character.SetHp(HP);
		character.SetMp(MP);
	}

	character.SetMaxHp(HP);
	character.SetMaxMp(MP);
	character.SetAttack(ATTACK);
	character.SetDamageReduction(character.GetCharacterStat().STR + 1);
	character.SetAccuracy(character.GetCharacterStat().DEX + 50);
	character.SetSkillEnhancement(character.GetCharacterStat().INT * 5);
	character.SetCriticalChance(character.GetCharacterStat().LUK * 2);
	character.SetStatStockAll(
		character.GetCharacterStat().STR
		+ character.GetCharacterStat().DEX
		+ character.GetCharacterStat().INT
		+ character.GetCharacterStat().LUK);
}

void CharacterManager::PrintCharacterInfoAll()
{
	Character* character = Character::GetInstance();
	system("cls");
	if (character != nullptr)
	{
		cout << "\n====================================================================" << endl;
		cout << "[ " << character->GetName() << " ] 님의 능력치입니다." << endl;
		cout << " * 레벨: " << character->GetLevel() <<  " LV" << endl;
		cout << " * HP: " << character->GetHp() << " / " << character->GetMaxHp() << endl;
		cout << " * MP: " << character->GetMp() << " / " << character->GetMaxMp() << endl;
		cout << " * 공격력: " << character->GetAttack() << endl;
		PrintCharacterInfoStat(character->GetCharacterStat());
		cout << " * 방어: " << character->GetDamageReduction() << endl;
		cout << " * 명중률: " << character->GetAccuracy() << " %" << endl;
		cout << " * 스킬데미지증가율: " << character->GetSkillEnhancement() << " %" << endl;
		cout << " * 치명타율: " << character->GetCriticalChance() << " %" << endl;
		cout << " * 경험치: " << character->GetExperience() << " / " << character->GetExperienceCapacity() << endl;
		cout << " * 골드: " << character->GetGold() << " 원" << endl;
		cout << "====================================================================" << endl;
	}
	else
	{
		cout << "캐릭터가 존재하지 않습니다...." << endl;
	}

}

void CharacterManager::PrintCharacterInfoStat(CharacterStat stat)
{
	cout << " * STR: " << stat.STR << endl;
	cout << " * DEX: " << stat.DEX << endl;
	cout << " * INT: " << stat.INT << endl;
	cout << " * LUK: " << stat.LUK << endl;

}

void CharacterManager::SetCharacterStat()
{
	int choice = 0;
	bool isComplete = false;

	Character* character = Character::GetInstance();
	if (character != nullptr)
	{
		
		CharacterStat stat = character->GetCharacterStat();
		int statStock = character->GetStatStock();

		while (!isComplete)
		{
			system("cls");
			cout << "현재 플레이어의 스텟 정보입니다.===========================" << endl;
			PrintCharacterInfoStat(stat);
			cout << "===========================================================" << endl;
			cout << "남은스텟: " << statStock << " POINT" << endl;
			cout << "[1]. STR ↑ / [2]. STR ↓" << endl;
			cout << "[3]. DEX ↑ / [4]. DEX ↓" << endl;
			cout << "[5]. INT ↑ / [6]. INT ↓" << endl;
			cout << "[7]. LUK ↑ / [8]. LUK ↓" << endl;
			cout << "[9]. 저장하기" << endl;
			cout << "[0]. 뒤로가기" << endl;
			cout << "선택: ";
			cin >> choice;

			if (cin.fail())
			{
				cout << "숫자만 입력가능합니다." << endl;
				Sleep(500);
				cin.clear();
				cin.ignore();

				continue;
			}

			// 뒤로가기
			if (choice == 0)
			{
				break;
			}

			// 저장하기
			if (choice == 9)
			{
				character->SetStatStock(statStock);
				character->SetCharacterStat(stat);
				GenerateCharacter(*character, false);
				break;
			}

			// 초과해서 찍지 못하도록
			if (statStock == character->GetStatStock() && choice % 2 == 0)
			{
				continue;
			}

			if (statStock > 0 || choice % 2 == 0)
			{
				switch (choice)
				{
				case 1:
					stat.STR++;
					statStock--;
					break;
				case 2:
					if (stat.STR > 0)
					{
						stat.STR--;
						statStock++;
					}
					break;
				case 3:
					stat.DEX++;
					statStock--;
					break;
				case 4:
					if (stat.DEX > 0)
					{
						stat.DEX--;
						statStock++;
					}
					break;
				case 5:
					stat.INT++;
					statStock--;
					break;
				case 6:
					if (stat.INT > 0)
					{
						stat.INT--;
						statStock++;
					}
					break;
				case 7:
					stat.LUK++;
					statStock--;
					break;
				case 8:
					if (stat.LUK > 0)
					{
						stat.LUK--;
						statStock++;
					}
					break;
				default:
					cout << "잘못된 입력입니다." << endl;
					Sleep(500);
					break;
				}
			}
			else
			{
				cout << "능력치를 올릴 스텟이 존재하지 않습니다." << endl;
				Sleep(1000);
				continue;
			}

		}
		Renderer::GetInstance()->RenderAll();
	}

}

void CharacterManager::SetCharacterStatAfterLevelUp()
{
	Character* character = Character::GetInstance();

	Cursor::SetTextColor(RGB(255, 255, 255));
	system("cls");
	cout << "축하드립니다 캐릭터가 " << character->GetLevel() << " LV 으로 레벨업하였습니다!" << endl;
	cout << "잠시후 스탯관리창으로 넘어갑니다." << endl;
	Sleep(2000); 

	SetCharacterStat();
	// 캐릭터 스텟 레벨업 후로 재설정 후 회복 및 경험치 수정
	character->SetHp(character->GetMaxHp());
	character->SetMp(character->GetMaxMp());

	// 레벨업
	SetCharacterExp(1);
}

void CharacterManager::SetCharacterExp(int caseNum) // caseNum 1: 레벨업, 2: 사망
{
	Character* character = Character::GetInstance();
	int exp = character->GetExperience();
	int expCapacity = character->GetExperienceCapacity();

	if (caseNum == 1)
	{
		// 현재 경험치 exp - expCapacity;
		character->SetExperience(exp - expCapacity);
		// 이 후에 경험치 총량을 기존 총량에 캐릭터레벨 * 10 을 더해줌
		character->SetExperienceCapacity(expCapacity + character->GetLevel() * 10);
	}
	else
	{
		// 사망? 
	}

	// 만약 경험치가 음수이면 0으로 초기화
	if (character->GetExperience() < 0)
	{
		character->SetExperience(0);
	}

}

unordered_map<string, string> CharacterManager::GetCharacterStat() const
{
	Character* character = Character::GetInstance();
	CharacterStat ability = character->GetCharacterStat();
	unordered_map<string, string> stat;

	stat["level"] = to_string(character->GetLevel());
	stat["hp"] = to_string(character->GetHp());
	stat["maxHp"] = to_string(character->GetMaxHp());
	stat["mp"] = to_string(character->GetMp());
	stat["maxMp"] = to_string(character->GetMaxMp());
	stat["attack"] = to_string(character->GetAttack());
	stat["exp"] = to_string(character->GetExperience());
	stat["maxExp"] = to_string(character->GetExperienceCapacity());
	stat["gold"] = to_string(character->GetGold());
	stat["damageReduction"] = to_string(character->GetDamageReduction());
	stat["accuracy"] = to_string(static_cast<int>(character->GetAccuracy()));
	stat["skillEnhancement"] = to_string(static_cast<int>(character->GetSkillEnhancement()));
	stat["criticalChance"] = to_string(static_cast<int>(character->GetCriticalChance()));
	stat["name"] = character->GetName();
	stat["str"] = to_string(ability.STR);
	stat["dex"] = to_string(ability.DEX);
	stat["int"] = to_string(ability.INT);
	stat["luk"] = to_string(ability.LUK);

	return stat;
}

// ============================= 스킬 관련 =======================================
void CharacterManager::CharacterGetSkill()
{
	Character* character = Character::GetInstance();
	SkillManager* skillManager = SkillManager::GetInstance();
	unique_ptr<Skill> skill = skillManager->TakeSkillRandom();

	if (skill != nullptr)
	{
		character->TakeSkill(move(skill));
	}
}