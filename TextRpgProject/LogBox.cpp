#include "LogBox.h"
#include "Cursor.h"
#include <iostream>

string LogBox::AddBorderPiece(const string& text) const
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

void LogBox::Print(const string& text, RGB color)
{
    logs.push_back({text, color});
    LogBox::checkFull();
    LogBox:Erase();

    Pos pos = ++LogBox::GetPos();
    for (LogAttr log : logs)
    {
    Cursor::SetPosition(pos);
    Cursor::SetTextColor(log.color);
    cout << log.text;
    pos.Y += 1;
    }
}

//void LogBox::Erase()
//{
//    Pos pos = ++LogBox::GetPos();
//    for (int i = 0; i < LogBox::GetSize().Y - 2; i++)
//    {
//        Cursor::SetPosition(pos);
//        cout << string(LogBox::GetSize().X - 2, ' ');
//        pos.Y += 1;
//    }
//}

void LogBox::clear()
{
    if (logs.empty()) return;

    logs.clear();
}

void LogBox::checkFull()
{
    int height = LogBox::GetSize().Y - 2;
    if (logs.size() > height)
    {
        logs.pop_front();
    }
}
