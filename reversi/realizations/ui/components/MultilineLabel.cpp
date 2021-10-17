//
// Created by Dawan on 18.10.2021.
//

#include "MultilineLabel.h"

MultilineLabel::MultilineLabel(int x, int y, int width, int height, int maxLines, bool centerAlign, bool singleLine) :
        centerAlign(centerAlign), singleLine(singleLine), maxLines(maxLines) {
    rect = { x, y, x + width, y + (height + 3) * maxLines};
}

void MultilineLabel::addLine(string line) {
    if (maxLines < lines.size()) {
        std::pop_heap(lines.begin(), lines.end());
    }
    lines.push_back(line);
}

void MultilineLabel::onPaint(HDC hdc) const {
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, color);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);

    long flags = DT_VCENTER;
    flags |= (singleLine) ? DT_SINGLELINE : 0L;
    flags |= (centerAlign) ? DT_CENTER : DT_LEFT;

    ostringstream o;
    for (const string& line : lines) {
        o << line << "\n";
    }

    DrawText(hdc, TEXT (o.str().c_str()), -1, const_cast<LPRECT>(&this->rect), flags);
}

RECT MultilineLabel::getViewRect() const {
    return rect;
}
void MultilineLabel::setColor(COLORREF color) {
    this->color = color;
}
