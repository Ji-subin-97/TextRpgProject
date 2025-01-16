#include "InputBox.h"
#include "LogBox.h"
#include <iostream>
#include "Cursor.h"
#include "Util.h"

using namespace std;

string InputBox::AddBorderPiece(const string& text) const
{
    string str;
    int text_length = (int)text.size();
    int width = this->GetSize().X;
    Border border = this->GetBorder();

    int start = 1;
    int index = 0;

    str.push_back(border.left);
    for (int i = 0; i < width - 2; i++)
    {
        if (i >= start && index < text_length)
        {
            str.push_back(text[index]);
            index++;
        }
        else
        {
            str.push_back(' ');
        }
    }
    str.push_back(border.right);

    return str;
}

string InputBox::Input()
{
    Pos pos = ++InputBox::GetPos();
    pos.X += 8;
    Cursor::SetPosition(pos);
    Cursor::ShowCursor();

    string str = Util::inputText(20);
    InputBox::Erase();
    Cursor::HideCursor();

    return str;
}

int InputBox::InputNumber()
{
    int choice = -1;
    try
    {
        choice = stoi(InputBox::GetInstance()->Input());
    }
    catch (const std::invalid_argument& e)
    {
        LogBox::GetInstance()->Print("유효하지 않은 숫자 형식입니다.", RGB(255, 0, 0));
    }
    catch (...)
    {
        LogBox::GetInstance()->Print("알 수 없는 오류가 발생했습니다.", RGB(255, 0, 0));
    }
    return choice;
}

void InputBox::Erase()
{
    Pos pos = ++this->GetPos();
    pos.X += 8;
    Cursor::SetPosition(pos);
    cout << string(this->GetSize().X - 10, ' ');
}

InputBox::InputBox()
{
    this->SetText("입력 : ");
}