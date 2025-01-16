#pragma once

#include "Box.h"

class TextBox : public Box
{
	string text;
private:
	virtual string AddBorderPiece(const string& text) const;
	void AddBorder() override;
public:
	TextBox();
	TextBox(const string& _text);
	void SetText(const string& _text);
	string GetText() const;
	void Erase();
};

