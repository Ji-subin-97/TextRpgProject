#include "TextBox.h"
#include "Cursor.h"
#include <iostream>
using namespace std;

string TextBox::AddBorderPiece(const string& text) const
{
    string str;
    int text_length = (int)text.size();
    int width = this->GetSize().X;
    Border border = this->GetBorder();

    int start = (width - 2 - text_length) / 2;
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


void TextBox::AddBorder()
{
    vector<string> body;
    int height = this->GetSize().Y;
    if (height < 3) height = 3;

    body.push_back(MakeLine(LineType::top));
    for (int i = 0; i < height - 2; i++)
    {
        body.push_back(MakeLine(LineType::middle));
    }
    body.push_back(MakeLine(LineType::bottom));

    int text_index = height % 2 == 0 ? (height / 2) - 1 : height / 2;
    body[text_index] = AddBorderPiece(this->text);

    this->SetBody(body);
}

TextBox::TextBox()
{
    this->SetText("");
}

TextBox::TextBox(const string& _text)
{
    this->SetText(_text);
}

void TextBox::SetText(const string& _text)
{
	text = _text;
    int size = (int)_text.size();
    int width = this->GetSize().X;
    int height = this->GetSize().Y;

    if (size > width - 2) {
        width = size + 2;
        this->SetSize(width, height);
    }

    AddBorder();
}

void TextBox::Erase()
{
    Pos pos = ++this->GetPos();
    for (int i = 0; i < this->GetSize().Y - 2; i++)
    {
        Cursor::SetPosition(pos);
        cout << string(this->GetSize().X - 2, ' ');
        pos.Y += 1;
    }
}
