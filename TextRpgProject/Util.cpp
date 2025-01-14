#include "Util.h"
#include <random>
#include <fstream>
#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>
#include <conio.h>
#include <iostream>

string Util::Trim(const string& str)
{
    // 문자 앞부분 공백이 끝나는 부분
    size_t start = str.find_first_not_of(" \t\n\r");
    // 문자 뒷부분 공백이 시작하는 부분
    size_t end = str.find_last_not_of(" \t\n\r");

    //문자열을 끝까지 읽는 동안 공백 외의 문자가 없으면 "" 반환
    if (start == string::npos || end == string::npos)  return "";

    //문자열 인덱스 start 부터 시작하고, 문자열의 길이 (end - start + 1) 만큼 자르고 반환
    return str.substr(start, end - start + 1);
}

int Util::GetRandomValue(int maxCount)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, maxCount);

    return dist(gen);
}

bool Util::DoesPassProbability(int percent)
{
    int value = GetRandomValue(100);

    if (value <= percent) return true;

    return false;
}

vector<string> Util::ReadText(const string& filename)
{
    // txt 파일 경로
    string path = ".\\asset\\" + filename + ".txt";
    ifstream file(path);

    // 파일이 열리지 않으면 에러 텍스트 반환
    if (!file.is_open()) return vector<string> {"ERROR"};

    // 파일 내용을 한 줄씩 읽어 출력
    vector<string> body;
    string line;
    while (getline(file, line)) body.push_back(line);

    file.close();

    return body;
}

int Util::GetLongestStringSize(vector<string>& text)
{
    int longest = 0;

    for (const string& str : text)
    {
        int size = (int)str.size();
        if (size > longest) longest = size;
    }

    return longest;
}

Pos Util::GetConsoleWindowSize()
{
    // 콘솔 핸들 가져오기
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // 콘솔 버퍼 및 창 정보 저장 구조체
    CONSOLE_SCREEN_BUFFER_INFO csbi = {};
    if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
    {
        int width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        int height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

        return Pos(width, height);
    }
    return Pos(2, 2);
}

string Util::inputText(int maxLength)
{
    string str;

    while (true) {
        char ch = _getch();  // 문자를 입력받되 콘솔에 자동 출력되지 않음
        if (ch == '\r') break;  // Enter 키로 입력 종료

        if (ch == '\b') {  // 백스페이스 처리
            if (!str.empty()) {
                str.pop_back();  // 마지막 문자 제거
                std::cout << "\b \b";  // 콘솔에서 한 문자 지우기
            }
            continue;
        }

        if (str.length() >= maxLength) continue;
        str.push_back(ch);
        cout << ch;
    }
    
    return str;
}
