#include <iostream>
#include <Windows.h>
#include "GameManager.h"
#include "CharacterManager.h"
#include "SkillManager.h"
#include "BattleManager.h"

using namespace std;

CharacterManager* characterManager;
BattleManager* battleManager;
SkillManager* skillManager;
static Character* curCharacter;

void GameManager::Init()
{
	characterManager = CharacterManager::GetInstance();
	battleManager = BattleManager::GetInstance();
	skillManager = SkillManager::GetInstance();

	battleManager->Init();
}

void GameManager::CreateCharacter()
{
	cout << "----------------------------------------------" << endl;
	cout << "|                  TEXT RPG                  |" << endl;
	cout << "----------------------------------------------" << endl;

	characterManager->CreateCharacter();							// ĳ���� ����
	curCharacter = characterManager->GetCharacter();				// ���� ĳ��������

	cout << "ĳ���� �����Ϸ�!" << endl;
	Sleep(2000);
}

bool GameManager::Main()
{
	system("cls");
	cout << "[ " << curCharacter->GetName() << " ] �� �������. ���Ͻô� �ൿ�� �������ּ���!" << endl;
	characterManager->PrintCharacterInfoAll();

	int choice = 0;

	cout << "\n1. ����" << endl;
	cout << "2. ĳ���� ���ݰ���" << endl;
	cout << "3. �κ��丮" << endl;
	cout << "4. ����" << endl;
	cout << "5. ����" << endl;

	cout << "\n�ൿ ����: ";
	cin >> choice;

	if (cin.fail())
	{
		cout << "���ڸ� �Է°����մϴ�." << endl;
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
		cout << "�޴��� �ش�Ǵ� ��ȣ�� �Է����ּ���." << endl;
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
		cout << "���� ��������: " << battleManager->GetBattleLevel() << " LV" << endl;

		cout << "\n1. ��������" << endl;
		cout << "2. ������������" << endl;
		cout << "3. ����ȭ��" << endl;
		cout << "�ൿ ����: ";
		cin >> choice;

		if (cin.fail())
		{
			cout << "���ڸ� �Է°����մϴ�." << endl;
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
				cout << "�������� ������ �����Ͽ����ϴ�. �ٽ� �õ����ּ���." << endl;
			}
			break;
		case 2:
			while (true)
			{
				cin.ignore();
				cout << "���Ͻô� ���������� �Է����ּ���. (1LV ~ 5LV)" << endl;
				cout << "�Է�: ";
				cin >> choice;

				if (cin.fail())
				{
					cout << "���ڸ� �Է°����մϴ�." << endl;
					cin.clear();
					cin.ignore();

					continue;
				}

				if (choice < 1 || choice > 5)
				{
					cout << "���������� 1LV ~ 5LV������ �Է°����մϴ�." << endl;
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
			cout << "�޴��� �ش�Ǵ� ��ȣ�� �Է����ּ���." << endl;
			continue;
			break;
		}
	}
}

void GameManager::EndGame()
{
	cout << "������ �����մϴ�." << endl;

	skillManager->DeleteInstance();
	characterManager->DeleteInstance();
	battleManager->DeleteInstance();
	this->DeleteInstance();
}

