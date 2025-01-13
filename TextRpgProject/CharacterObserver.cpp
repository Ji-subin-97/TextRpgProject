#include "CharacterObserver.h"
#include "CharacterManager.h"

void CharacterManagerSystem::LevelUpEvent()
{
	CharacterManager::GetInstance()->SetCharacterStatAfterLevelUp();
}