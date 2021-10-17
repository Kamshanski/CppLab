#include "includeAll.h"
#include "RadioButtonGroup.h"


const COLORREF RadioButtonGroup::SELECTED = Color::BLACK;
const COLORREF RadioButtonGroup::CLEAR = Color::WHITE;
const COLORREF RadioButtonGroup::LINE_COLOR = Color::BLACK;
const int RadioButtonGroup::HORIZONTAL_GAP = 6;
const int RadioButtonGroup::VERTICAL_GAP = 6;
const int RadioButtonGroup::SIZE = 22;
const int RadioButtonGroup::TEXT_WIDTH = 140;

RadioButtonGroup::RadioButtonGroup(int x, int y, vector<string> options, int selectedIndex) :
        options(options), x(x), y(y), selectedIndex(selectedIndex) {
    if (options.size() < 2) {
        throw std::invalid_argument("Options vector size cannot be less than 2");
    }
    startX = x;
    startY = y;
    int size = options.size();
    endX = x + size * (SIZE + HORIZONTAL_GAP + TEXT_WIDTH);
    endY = y + size * (SIZE) + (size - 1) * (VERTICAL_GAP);
}

void RadioButtonGroup::onPaint(HDC hdc) const {
    int size = options.size();
    for (int i = 0; i < size; ++i) {
        COLORREF color = (selectedIndex != i) ? CLEAR : SELECTED;
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, color);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, LINE_COLOR);

        int rY = y + (i * (SIZE + VERTICAL_GAP));
        int rX = x;
        Ellipse(hdc, rX, rY, rX + SIZE, rY + SIZE);

        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, Color::BLACK);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, Color::BLACK);

        RECT textRect = {
                rX + SIZE + HORIZONTAL_GAP,
                rY,
                rX + SIZE + HORIZONTAL_GAP + TEXT_WIDTH,
                rY + SIZE};
        DrawText(hdc, TEXT (options[i].c_str()), -1, &textRect,
                 DT_SINGLELINE | DT_LEFT | DT_VCENTER);
    }
}



bool RadioButtonGroup::onClick(int pX, int pY) {
    int clickedIndex = findOptionByCoords(pX, pY);
    if (clickedIndex > -1 && selectedIndex != clickedIndex) {
        selectedIndex = clickedIndex;
        return true;
    }
    return false;
}

int RadioButtonGroup::findOptionByCoords(int pX, int pY) {
    int size = options.size();
    int centerX = x + (SIZE / 2);
    int centerY = y + (SIZE / 2);
    float radiusSquared = pow(SIZE / 2, 2);
    for (int i = 0; i < size; ++i) {
        int radioX = centerX;
        int radioY = centerY + i * (SIZE + VERTICAL_GAP);
        if (pow(pX - radioX, 2) + pow(pY - radioY, 2) <= radiusSquared) {
            return i;
        }
    }
    return -1;
}


