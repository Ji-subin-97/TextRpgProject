#pragma once

#include <string>
#include "Singleton.h"
#include "Pawn.h"
#include "struct.h"

using namespace std;
 
class Player : public Singleton<Player>
{
private:
	friend class Singleton<Player>;
	Pawn* playerBody;
protected:
	Player() = default;
	~Player();
public:
	void SelectRace(PawnId id = PawnId::HUMAN);
	void SetName(const string& name);
	string GetName() const;
	Pawn* GetPlayerBody() const;
};