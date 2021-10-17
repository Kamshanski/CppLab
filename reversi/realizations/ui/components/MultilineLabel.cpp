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
        lines.erase(lines.begin());
    }
    ostringstream o;
    std::time_t t = std::time(nullptr);   // get time now
    std::tm* now = std::localtime(&t);
    o << std::setfill('0') << std::setw(2) << now->tm_hour << ':'
      << std::setfill('0') << std::setw(2) << now->tm_min << ':'
      << std::setfill('0') << std::setw(2) << now->tm_sec << " >> "
      << line;
    cout << o.str()<<endl;
    lines.push_back(o.str());
}

void MultilineLabel::onPaint(HDC hdc) const {
    // clear previous text
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, Color::WHITE);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, Color::WHITE);
    Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);

    // draw new text
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, color);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, color);
    long flags = DT_VCENTER;
    flags |= (singleLine) ? DT_SINGLELINE : 0L;
    flags |= (centerAlign) ? DT_CENTER : DT_LEFT;

    ostringstream o;
    for (int i = lines.size() - 1; i >= 0; --i) {
        o << lines[i] << "\n";
    }

    DrawText(hdc, TEXT (o.str().c_str()), -1, const_cast<LPRECT>(&this->rect), flags);
}

RECT MultilineLabel::getViewRect() const {
    return rect;
}
void MultilineLabel::setColor(COLORREF color) {
    this->color = color;
}
