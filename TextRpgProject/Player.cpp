#include "Player.h"
#include "Human.h"

Player::~Player()
{
	delete playerBody;
}

//void Player::SelectRace(PawnId id)
//{
//	switch (id)
//	{
//		case PawnId::HUMAN :
//		{
//			playerBody = new Human(1);
//		}
//	}
//}

void Player::SetName(const string& name)
{
	playerBody->setName(name);
}

string Player::GetName() const
{
	return playerBody->getName();
}

Pawn* Player::GetPlayerBody() const
{
	if (playerBody != nullptr) return playerBody;
	return nullptr;
}
