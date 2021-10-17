#include "includeAll.h"

Label::Label(int x, int y, int width, int height, bool centerAlign, bool singleLine) :
        centerAlign(centerAlign), singleLine(singleLine) {
    rect = { x, y, x + width, y + height};
}

void Label::onPaint(HDC hdc) const {
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, color);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);

    long flags = DT_VCENTER;
    flags |= (singleLine) ? DT_SINGLELINE : 0L;
    flags |= (centerAlign) ? DT_CENTER : DT_LEFT;

    DrawText(hdc, TEXT (text.c_str()), -1, const_cast<LPRECT>(&this->rect), flags);
}

void Label::setColor(COLORREF color) {
    this->color = color;
}

void Label::setText(string text) {
    this->text = std::move(text);
}

