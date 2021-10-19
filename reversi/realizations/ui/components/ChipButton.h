#pragma once
#include "includeAll.h"

class ChipButton : public Drawable  {
public:
    static const COLORREF BTN_SELECTED;
    static const COLORREF BTN_HIGHLIGHTED;
    static const COLORREF BTN_CLEAR;
    static const COLORREF CHIP_BLACK;
    static const COLORREF CHIP_WHITE;
    static const COLORREF LINE_COLOR;

private:
    int x, y;
    int btnSize;
    int chipSize;

    RECT btnRect;
    COLORREF btnColor = BTN_CLEAR;

    bool showChip = false;
    RECT chipRect;
    COLORREF chipColor = CHIP_BLACK;


public:
    ChipButton(int x, int y, int btnSize, int chipSize);

    void onPaint(HDC hdc) const override;

    RECT getViewRect() const override;

    bool containsPoint(int pX, int pY);

    // setters
    void setBtnColor(COLORREF btnColor);
    void setChipVisibility(bool showChip);
    void setChipColor(COLORREF chipColor);
    // getter only for test
    bool isChipVisible() const;
    int getChipSize() const;

    RECT getChipRect() const;
};