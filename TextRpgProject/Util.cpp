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
    // ���� �պκ� ������ ������ �κ�
    size_t start = str.find_first_not_of(" \t\n\r");
    // ���� �޺κ� ������ �����ϴ� �κ�
    size_t end = str.find_last_not_of(" \t\n\r");

    //���ڿ��� ������ �д� ���� ���� ���� ���ڰ� ������ "" ��ȯ
    if (start == string::npos || end == string::npos)  return "";

    //���ڿ� �ε��� start ���� �����ϰ�, ���ڿ��� ���� (end - start + 1) ��ŭ �ڸ��� ��ȯ
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
    // txt ���� ���
    string path = ".\\asset\\" + filename + ".txt";
    ifstream file(path);

    // ������ ������ ������ ���� �ؽ�Ʈ ��ȯ
    if (!file.is_open()) return vector<string> {"ERROR"};

    // ���� ������ �� �پ� �о� ���
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
    // �ܼ� �ڵ� ��������
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // �ܼ� ���� �� â ���� ���� ����ü
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
        char ch = _getch();  // ���ڸ� �Է¹޵� �ֿܼ� �ڵ� ��µ��� ����
        if (ch == '\r') break;  // Enter Ű�� �Է� ����

        if (ch == '\b') {  // �齺���̽� ó��
            if (!str.empty()) {
                str.pop_back();  // ������ ���� ����
                std::cout << "\b \b";  // �ֿܼ��� �� ���� �����
            }
            continue;
        }

        if (str.length() >= maxLength) continue;
        str.push_back(ch);
        cout << ch;
    }
    
    return str;
}
