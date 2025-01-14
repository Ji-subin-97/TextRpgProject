#pragma once
#include "TextBox.h"
#include "SingleTon.h"

class InputBox : public TextBox, public SingleTon<InputBox>
{
    friend class SingleTon<InputBox>;
    InputBox();
    InputBox(const string& _text) = delete;
private:
    string AddBorderPiece(const string& text) const override;
public:
    string Input();
    void Erase();
};

