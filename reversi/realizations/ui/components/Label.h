#pragma once
#include "includeAll.h"
class Label : public Drawable {
private:
    string text = "";
    COLORREF color = Color::BLACK;
    bool centerAlign = false;
    bool singleLine = true;
    RECT rect;

public:
    Label(int x, int y, int width, int height, bool centerAlign = false, bool singleLine = true);

    void onPaint(HDC hdc) const override;
    RECT getViewRect() const override;
    void setColor(COLORREF chipColor);

    void setText(string text);
    void clearText();
};

