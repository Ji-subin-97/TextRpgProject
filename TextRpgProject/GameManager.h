#pragma once
#include "SingleTon.h"

class GameManager : public SingleTon<GameManager>
{
private:
	GameManager() = default;
	~GameManager() = default;
	friend class SingleTon<GameManager>;
public:
	void Init();					// ���� �ʱ⼼��
	void CreateCharacter();			// �÷��̾� ����
	bool Main();					// ����ȭ��
	void Battle();					// ����ȭ��
};