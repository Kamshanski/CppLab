#pragma once
#include "includeAll.h"
class MultilineLabel : public Drawable  {
    int maxLines = 1;
    vector<string> lines;
    COLORREF color = Color::BLACK;
    bool centerAlign = false;
    bool singleLine = true;
    RECT rect;
public:
    MultilineLabel(int x, int y, int width, int height, int maxLines, bool centerAlign = false, bool singleLine = false);

    void addLine(string line);
    void onPaint(HDC hdc) const override;
    RECT getViewRect() const override;
    void setColor(COLORREF chipColor);
};
