#pragma once

using uInt8 = unsigned __int8;
using uInt16 = unsigned __int16;
using uInt32 = unsigned __int32;

enum class ForeColor : int
{
    Black = 30,
    Red = 31,
    Green = 32,
    Yellow = 33,
    Blue = 34,
    Magenta = 35,
    Cyan = 36,
    White = 37,
    Default = 39,
    BrightBlack = 90,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93,
    BrightBlue = 94,
    BrightMagenta = 95,
    BrightCyan = 96,
    BrightWhite = 97,
    Reset = 0,
};

enum class BackColor : int
{
    Black = 40,
    Red = 41,
    Green = 42,
    Yellow = 43,
    Blue = 44,
    Magenta = 45,
    Cyan = 46,
    White = 47,
    Default = 49,
    BrightBlack = 100,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    BrightBlue = 104,
    BrightMagenta = 105,
    BrightCyan = 106,
    BrightWhite = 107,
    Reset = 0,
};

enum class TextStyle : int
{
    Reset,
    Bold,
    Dim,
    Italic,
    Underline,
    Blinking,
    Inverse,
    Invisible,
    Strikethrough,
};

struct Border
{
    char top;
    char top_right;
    char right;
    char bottom_right;
    char bottom;
    char bottom_left;
    char left;
    char top_left;
};

enum class LineType : char
{
    top,
    middle,
    bottom
};

// 행렬 위치 구조체
struct Pos {
    int X;
    int Y;

    Pos()
    {
        X = 0;
        Y = 0;
    }
    Pos(int _x, int _y)
    {
        X = _x;
        Y = _y;
    }
    Pos operator+(const Pos& other) const
    {
        return Pos(X + other.X, Y + other.Y);
    }
    Pos operator-(const Pos& other) const
    {
        return Pos(X - other.X, Y - other.Y);
    }
    Pos operator++() const
    {
        return Pos(X + 1, Y + 1);
    }
};

#ifdef RGB
#undef RGB
#endif

// RGB 구조체
// uInt8 : 0 ~ 255 사이의 숫자로 unsigned __int8 줄임말
struct RGB {
    uInt8 r;
    uInt8 g;
    uInt8 b;

    RGB() : r(255), g(255), b(255) {}
    RGB(uInt8 _r, uInt8 _g, uInt8 _b) : r(_r), g(_g), b(_b) {}
};