#include "Cursor.h"
#include <string>
#include <iostream>

using namespace std;

const string ESC = "\x1B";
const string CSI = "\x9B";
const string DCS = "\x90";
const string OSC = "\x9D";

void Cursor::MoveUp(int count) {
	cout << ESC << count << "A";
}

void Cursor::MoveDown(int count) {
	cout << ESC << count << "B";
}

void Cursor::MoveLeft(int count) {
	cout << ESC << count << "D";
}

void Cursor::MoveRight(int count) {
	cout << ESC << count << "C";
}

void Cursor::SetPosition(int x, int y) {
	cout << ESC << "[" << y << ";" << x << "H";
}

void Cursor::SetPosition(Pos pos) {
	cout << ESC << "[" << pos.Y << ";" << pos.X << "H";
}

void Cursor::ClearScreen() {
	cout << ESC << "[J";
}

void Cursor::ClearLine(int line) {
	SetPosition(line, 1);
	ClearCurrentLine();
}

void Cursor::ClearCurrentLine()
{
	cout << ESC << "[2K";
}

void Cursor::HideCursor()
{
	cout << ESC << "[?25l";
}

void Cursor::ShowCursor()
{
	cout << ESC << "[?25h";
}

void Cursor::SetTextColor(ForeColor color)
{
	cout << ESC << "[" << (int)color << "m";
}
void Cursor::SetTextColor(RGB color)
{
	cout << ESC << "[38;2;" << color.r << ";" << color.g << ";" << color.b << "m";
}

void Cursor::ResetTextColor()
{
	SetTextColor(ForeColor::Default);
}

void Cursor::SetBackgroundColor(BackColor color)
{
	cout << ESC << "[" << (int)color << "m";
}

void Cursor::ResetBackgroundColor()
{
	SetBackgroundColor(BackColor::Default);
}
void Cursor::ResetAllStyle()
{
	ResetTextColor();
	ResetBackgroundColor();
	ResetTextStyle();
}

//template <typename... Args>
//void Cursor::SetTextStyle(Args... textstyle_args)
//{
//	cout << ESC << "[";
//	((cout << (int)textstyle_args << ";"), ...);
//	cout << "m";
//}
void Cursor::SetTextStyle(TextStyle style)
{
	cout << ESC << "[" << (int)style << ";" << "m";
}

void Cursor::ResetTextStyle()
{
	SetTextStyle(TextStyle::Reset);
}