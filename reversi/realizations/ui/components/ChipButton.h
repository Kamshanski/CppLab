#pragma once
#include "includeAll.h"

class ChipButton {
public:
    static const COLORREF SELECTED;
    static const COLORREF CLEAR;
    static const COLORREF CHIP_BLACK;
    static const COLORREF CHIP_WHITE;
    static const COLORREF LINE_COLOR;

    static const int SIZE;
    static const int CHIP_SIZE;

private:
    int x, y;

    RECT btnRect;
    COLORREF btnColor = CLEAR;

    bool showChip = false;
    RECT chipRect;
    COLORREF chipColor = CHIP_BLACK;


public:
    ChipButton(int x, int y);

    void onPaint(HDC hdc) const;

    bool containsPoint(int pX, int pY);

    // setters
    void setBtnColor(COLORREF btnColor);
    void setChipVisibility(bool showChip);
    void setChipColor(COLORREF chipColor);
    // getter only for test
    bool isChipVisible() const;
};