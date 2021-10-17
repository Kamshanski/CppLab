#include "includeAll.h"

Label::Label(int x, int y, int width, int height) : x(x), y(y), width(width), height(height) {
    rect = { x, y, x + width, y + height};
}

void Label::onPaint(HDC hdc) const {
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, Color::BLACK);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, Color::BLACK);
    DrawText(hdc, TEXT (text.c_str()), -1, const_cast<LPRECT>(&this->rect),
             DT_SINGLELINE | DT_LEFT | DT_VCENTER);
}

void Label::setColor(COLORREF color) {
    this->color = color;
}

void Label::setText(string text) {
    this->text = std::move(text);
}

