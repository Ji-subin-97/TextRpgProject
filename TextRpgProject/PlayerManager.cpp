#include "PlayerManager.h"
#include <iostream>
#include "Validator.h"
#include "Util.h"
bool PlayerManager::IsValid(const string& name)
{
	if (Validator::IsBlank(name))
	{
		cout << "������ �̸����� ����� �� �����ϴ�. �ٽ� �Է����ּ���." << endl;
		return false;
	}
	// �г��� ���� 1 ~ 20
	if (!Validator::IsValidLength(name, 1, 20))
	{
		cout << "�г��� ���̴� 20�� �ʰ��� �� �����ϴ�. �ٽ� �Է����ּ���." << endl;
		return false;
	}
    if (name.find('\\') != string::npos)
	{
		cout << "�г��ӿ� ������ �� ���� ���ڰ� �ֽ��ϴ�. �ٽ� �Է����ּ���." << endl;
		return false;
	}
	return true;
}

void PlayerManager::DisplayStat()
{
	Pawn* playerBody = player->GetPlayerBody();
	string name = playerBody->getName();
	cout << name << endl;
}

void PlayerManager::CreatePlayer()
{
	string name;

	while (true)
	{
	cout << "ĳ������ �̸��� �Է����ּ��� : ";
	getline(cin, name);
	name = Util::Trim(name);
	if (IsValid(name)) break;
	}
	player = Player::GetInstance();
	player->SelectRace();
	player->SetName(name);
}
