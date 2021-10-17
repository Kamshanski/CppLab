#pragma once
#include "includeAll.h"

class Button {
    int x, y;
    int index;
    volatile COLORREF color = Color::YELLOW;
    RECT btnRect;
    RECT chipEllipse;

public:
    static const int SIZE;
    static const int CHIP_SIZE;

    Button(int x, int y);

    void onPaint(HDC hdc) const;

    bool containsPoint(int pX, int pY);


    // getters setters
    pair<int, int> getPosition() const;
    void setPosition(int x, int y);
    COLORREF getColor() const;
    void setColor(COLORREF color);
};