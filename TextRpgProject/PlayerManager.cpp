#include "PlayerManager.h"
#include <iostream>
#include "Validator.h"
#include "Util.h"
bool PlayerManager::IsValid(const string& name)
{
	if (Validator::IsBlank(name))
	{
		cout << "공백은 이름으로 사용할 수 없습니다. 다시 입력해주세요." << endl;
		return false;
	}
	// 닉네임 길이 1 ~ 20
	if (!Validator::IsValidLength(name, 1, 20))
	{
		cout << "닉네임 길이는 20을 초과할 수 없습니다. 다시 입력해주세요." << endl;
		return false;
	}
    if (name.find('\\') != string::npos)
	{
		cout << "닉네임에 포함할 수 없는 문자가 있습니다. 다시 입력해주세요." << endl;
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
	cout << "캐릭터의 이름을 입력해주세요 : ";
	getline(cin, name);
	name = Util::Trim(name);
	if (IsValid(name)) break;
	}
	player = Player::GetInstance();
	player->SelectRace();
	player->SetName(name);
}
