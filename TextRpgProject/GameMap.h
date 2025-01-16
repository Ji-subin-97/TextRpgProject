#pragma once

#include "Container.h"
#include <memory>

using namespace std;

//루트컨테이너에서 고르면 됩니다.
namespace GameMap
{
	shared_ptr<Container> Index();
	shared_ptr<Container> SelectStat();
	shared_ptr<Container> Main();
	shared_ptr<Container> SelectBattle();
	shared_ptr<Container> Battle();
};