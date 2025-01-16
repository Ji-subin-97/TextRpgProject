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
	// txt 파일을 읽어서 vector<string>에 저장
	vector<string> ReadText(const string& filename);

	// 오브젝트의 너비를 구하는 함수
	int GetLongestStringSize(vector<string>& text);
	Pos GetConsoleWindowSize();
	string inputText(int maxLength);
};

