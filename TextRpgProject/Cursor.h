#pragma once
#include "UIStruct.h"

namespace Cursor
{
    // 커서 조작
    void MoveUp(int count);
    void MoveDown(int count);
    void MoveLeft(int count);
    void MoveRight(int count);
    void SetPosition(int x, int y);
    void SetPosition(Pos pos);
    // 지우기
    void ClearScreen();
    void ClearLine(int line);
    void ClearCurrentLine();
    // 커서 숨기기/보이기
    void HideCursor();
    void ShowCursor();
    // 색 변경 
    void SetTextColor(ForeColor color);
    void SetTextColor(RGB color);
    void ResetTextColor();
    void SetBackgroundColor(BackColor color);
    void ResetBackgroundColor();
    void ResetAllStyle();
    // 텍스트 스타일
    //template <typename... Args>
    //void SetTextStyle(Args... args);
    void SetTextStyle(TextStyle style);
    void ResetTextStyle();
};

