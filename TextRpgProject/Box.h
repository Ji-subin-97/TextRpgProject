#pragma once

#include "Object.h"
#include "UIStruct.h"

#include <string>

using namespace std;

class Box : public Object
{
    //int padding = 0;
    //int margin = 0;
    // 12시(top) 부터 시계 방향 순
    Border border = { '-','*','|','*','-','*','|','*' };
protected:
    string MakeLine(LineType type) const;
    virtual void AddBorder() = 0;
public:
    Box();
    Box(Pos pos);
    void SetSize(int _width, int _height);
    void SetSize(Pos size);
    void ExpandWidth(int value);
    void ExpandHeight(int value);
    //테두리 조절
    //void SetPadding(int value);
    //void SetMargin(int value);
    void SetBorder(Border _border);
    void SetBorderOnce(char style);
    void SetBorderCornerOnce(char style);
    void SetBorderMiddleOnce(char style);
    void SetBorderVerticalOnce(char style);
    void SetBorderHorizontalOnce(char style);
    //int GetPadding() const;
    //int GetMargin() const;
    Border GetBorder() const;
    //void LoadFromTxt(string filename) override;
};

