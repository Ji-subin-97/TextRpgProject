#pragma once
#include "UIStruct.h"

namespace Cursor
{
    // Ŀ�� ����
    void MoveUp(int count);
    void MoveDown(int count);
    void MoveLeft(int count);
    void MoveRight(int count);
    void SetPosition(int x, int y);
    void SetPosition(Pos pos);
    // �����
    void ClearScreen();
    void ClearLine(int line);
    void ClearCurrentLine();
    // Ŀ�� �����/���̱�
    void HideCursor();
    void ShowCursor();
    // �� ���� 
    void SetTextColor(ForeColor color);
    void SetTextColor(RGB color);
    void ResetTextColor();
    void SetBackgroundColor(BackColor color);
    void ResetBackgroundColor();
    void ResetAllStyle();
    // �ؽ�Ʈ ��Ÿ��
    //template <typename... Args>
    //void SetTextStyle(Args... args);
    void SetTextStyle(TextStyle style);
    void ResetTextStyle();
};

