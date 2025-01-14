#pragma once

#include "Box.h"

class TextBox : public Box
{
	string text;
private:
	string AddBorderPiece(string& text) const;
	void AddBorder() override;
public:
	TextBox();
	TextBox(const string& _text);
	void SetText(const string& _text);
};

