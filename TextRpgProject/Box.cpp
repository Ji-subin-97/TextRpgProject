#include "Box.h"
#include "Util.h"
#include "UIStruct.h"

Box::Box()
{
}
Box::Box(Pos pos)
{
    this->SetPos(pos);
}

void Box::SetSize(int _width, int _height)
{
    this->UpdateSize(_width, _height);
}

void Box::SetSize(Pos size)
{
    this->UpdateSize(size);
}

string Box::MakeLine(LineType type) const
{
    string line;
    char left = 0;
    char right = 0;
    char middle = 0;

    if (type == LineType::top)
    {
        left = border.top_left;
        right = border.top_right;
        middle = border.top;
    }
    if (type == LineType::bottom)
    {
        left = border.bottom_left;
        right = border.bottom_right;
        middle = border.bottom;
    }
    if (type == LineType::middle)
    {
        left = border.left;
        right = border.right;
        middle = ' ';
    }

    int width = this->GetSize().X;

    line.push_back(left);
    for (int i = 0; i < width - 2; i++)
    {
        line.push_back(middle);
    }
    line.push_back(right);

    return line;
}
void Box::SetPadding(int value)
{
    this->padding = value;
}
void Box::SetMargin(int value)
{
    this->margin = value;
}
//void Box::SetWidth(int value)
//{
//    this->width = value;
//}
//void Box::SetHeight(int value)
//{
//    this->height = value;
//}
void Box::SetBorder(Border _border)
{
    this->border = _border;
}
void Box::SetBorderOnce(char style)
{
    SetBorderMiddleOnce(style);
    SetBorderCornerOnce(style);
}
void Box::SetBorderCornerOnce(char style)
{
    border.top_left = style;
    border.top_right = style;
    border.bottom_left = style;
    border.bottom_right = style;
}
void Box::SetBorderMiddleOnce(char style)
{
    SetBorderHorizontalOnce(style);
    SetBorderVerticalOnce(style);
}
void Box::SetBorderVerticalOnce(char style)
{
    border.left = style;
    border.right = style;
}
void Box::SetBorderHorizontalOnce(char style)
{
    border.top = style;
    border.bottom = style;
}
int Box::GetPadding() const
{
    return this->padding;
}
int Box::GetMargin() const
{
    return this->margin;
}

//int Box::GetWidth() const
//{
//    return this->width;
//}
//
//int Box::GetHeight() const
//{
//    return this->height;
//}

Border Box::GetBorder() const
{
    return this->border;
}

void Box::LoadFromTxt(string filename)
{
    vector<string> body = Util::ReadText(filename);
    this->SetBody(body);
}
