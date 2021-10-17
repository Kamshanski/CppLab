#include "includeAll.h"
#include "Button.h"


/*
RECT
left Specifies the x-coordinate of the upper-left corner of the rectangle.
top Specifies the y-coordinate of the upper-left corner of the rectangle.
right Specifies the x-coordinate of the lower-right corner of the rectangle.
bottom Specifies the y-coordinate of the lower-right corner of the rectangle.
 */

const COLORREF Button::SELECTED = Color::YELLOW;
const COLORREF Button::CLEAR = Color::GREY;
const COLORREF Button::CHIP_BLACK = Color::BLACK;
const COLORREF Button::CHIP_WHITE = Color::WHITE;
const COLORREF Button::LINE_COLOR = Color::BLACK;
const int Button::SIZE = 50;
const int Button::CHIP_SIZE = 20;


Button::Button(int x, int y) : x(x), y(y) {
    btnRect = {x, y, x + Button::SIZE, y + Button::SIZE };
    int btnSize = Button::SIZE;
    int chipSize = Button::CHIP_SIZE;
    int dPlus = (btnSize + chipSize) / 2;
    int dMinus = (btnSize - chipSize) / 2;

    chipRect = {
            x + dMinus,
            y + dMinus,
            x + dPlus,
            y + dPlus
    };
}


void Button::onPaint(HDC hdc) const {
    SelectObject(hdc, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hdc, btnColor);
    SelectObject(hdc, GetStockObject(DC_PEN));
    SetDCPenColor(hdc, LINE_COLOR);

    Rectangle(hdc, btnRect.left, btnRect.top, btnRect.right, btnRect.bottom);

    if (showChip) {
        SelectObject(hdc, GetStockObject(DC_BRUSH));
        SetDCBrushColor(hdc, chipColor);
        SelectObject(hdc, GetStockObject(DC_PEN));
        SetDCPenColor(hdc, LINE_COLOR);

        Ellipse(hdc, chipRect.left, chipRect.top, chipRect.right, chipRect.bottom);
    }

}

bool Button::containsPoint(int pX, int pY) {
    return (x <= pX && pX <= (x + Button::SIZE)) &&
           (y <= pY && pY <= (y + Button::SIZE));
}



// setters
void Button::setBtnColor(COLORREF btnColor) { Button::btnColor = btnColor; }
void Button::setChipVisibility(bool showChip) { Button::showChip = showChip; }
void Button::setChipColor(COLORREF chipColor) { Button::chipColor = chipColor; }

bool Button::isChipVisible() const { return showChip; }




// старая функция
//int Button::onPaint(LPDRAWITEMSTRUCT item) {
////    if (modCount == drawCount) {
////        return TRUE;
////    }
//
////    static HFONT hfontButton = CreateFont(16, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET,
////                                          OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
////                                          DEFAULT_QUALITY, DEFAULT_PITCH, "Arial Black");
////
////    /* установить отображение текста */
////    SetBkMode(item->hDC, TRANSPARENT);
////    SetTextColor(item->hDC, Color::BLACK); // text color
////    SelectObject(item->hDC, hfontButton);
//
//    /* белый фон при нажатии */
//    FillRect(item->hDC, &item->rcItem,(HBRUSH)CreateSolidBrush(getColor()));
////    if(item->itemState & ODS_SELECTED)
////        FillRect(item->hDC, &item->rcItem, (HBRUSH)CreateSolidBrush(Color::WHITE));
////    else {
////        FillRect(item->hDC, &item->rcItem,(HBRUSH)CreateSolidBrush(getColor()));
////    }
//
//    /* нарисовать текст */
//    int len = GetWindowTextLength(item->hwndItem);
//    char* buf = new char[len + 1];
//    GetWindowTextA(item->hwndItem, buf, len + 1);
//    DrawTextA(item->hDC, buf, len, &item->rcItem, DT_CENTER);
//
//    drawCount = modCount;
//    return TRUE;
//}







