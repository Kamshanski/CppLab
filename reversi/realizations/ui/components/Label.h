#pragma once
#include "includeAll.h"
class Label : public Drawable {
    string text;
    int x, y;
    int width, height;
    RECT rect;
    COLORREF color = Color::BLACK;
public:
    Label(int x, int y, int width, int height);

    void onPaint(HDC hdc) const override;
    void setColor(COLORREF chipColor);

    void setText(string text);
};

