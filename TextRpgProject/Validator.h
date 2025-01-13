#pragma once

#include <string>

using namespace std;

namespace Validator
{
	bool IsBlank(const string& name);
	bool IsValidLength(const string& name, int min, int max);
};

