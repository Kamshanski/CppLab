#pragma once
#include "includeAll.h"
class Label {
    string text;
    int x, y;
    int width, height;
    RECT rect;
    COLORREF color = Color::BLACK;
public:
    Label(int x, int y, int width, int height);

    void onPaint(HDC hdc) const;
    void setColor(COLORREF chipColor);

    void setText(string text);


};

