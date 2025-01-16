#pragma once
#include "TextBox.h"
#include "SingleTon.h"
#include <string>
#include <deque>

using namespace std;

struct LogAttr
{
    string text;
    RGB color;
};

class LogBox : public TextBox, public SingleTon<LogBox>
{
    friend class SingleTon<LogBox>;
    LogBox() = default;
    LogBox(const string& _text) = delete;
    deque<LogAttr> logs;
private:
    string AddBorderPiece(const string& text) const override;
public:
    void Print(const string& text, RGB color = {255,255,255});
    //void Erase();
    void Clear();
    void CheckFull();
};
