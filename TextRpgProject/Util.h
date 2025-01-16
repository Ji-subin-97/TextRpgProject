#pragma once

#include <string>
#include <vector>
#include "UIStruct.h"

using namespace std;

namespace Util
{
	string Trim(const string& str);
	int GetRandomValue(int maxCount);
	bool DoesPassProbability(int percent);
	// txt ������ �о vector<string>�� ����
	vector<string> ReadText(const string& filename);

	// ������Ʈ�� �ʺ� ���ϴ� �Լ�
	int GetLongestStringSize(vector<string>& text);
	Pos GetConsoleWindowSize();
	string inputText(int maxLength);
};

