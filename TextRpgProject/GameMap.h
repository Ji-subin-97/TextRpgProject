#pragma once

#include "Container.h"
#include <memory>

using namespace std;

//��Ʈ�����̳ʿ��� ���� �˴ϴ�.
namespace GameMap
{
	shared_ptr<Container> Index();
	shared_ptr<Container> SelectStat();
	shared_ptr<Container> Main();
	shared_ptr<Container> SelectBattle();
	shared_ptr<Container> Battle();
};