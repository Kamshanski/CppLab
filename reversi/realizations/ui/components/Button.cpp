#include <utility>

#include "includeAll.h"
#include "Button.h"


Button::Button(int x, int y, int width, int height) {
    rect = { x, y, x + width, y + height};
}

bool Button::onClick(int pX, int pY) {
    if ((rect.left <= pX && pX <= rect.right) && (rect.top <= pY && pY <= rect.bottom)) {
        if (listener != nullptr) listener->onClicked();
        return true;
    }
    return false;
}

void Button::onPaint(HDC hdc) const {

    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, btnColor);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, lineColor);

    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, textColor);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, textColor);

    DrawText(hdc, TEXT (text.c_str()), -1, const_cast<LPRECT>(&rect), DT_SINGLELINE | DT_CENTER | DT_VCENTER);
}

void Button::setListener(ButtonListener *listener) { Button::listener = listener; }

void Button::setText(string text) {
    Button::text = std::move(text);
}

RECT Button::getViewRect() const {
    return rect;
}
