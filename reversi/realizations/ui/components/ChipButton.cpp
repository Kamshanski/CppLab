#include "includeAll.h"
#include "ChipButton.h"


/*
RECT
left Specifies the x-coordinate of the upper-left corner of the rectangle.
top Specifies the y-coordinate of the upper-left corner of the rectangle.
right Specifies the x-coordinate of the lower-right corner of the rectangle.
bottom Specifies the y-coordinate of the lower-right corner of the rectangle.
 */

const COLORREF ChipButton::SELECTED = Color::YELLOW;
const COLORREF ChipButton::CLEAR = Color::GREY;
const COLORREF ChipButton::CHIP_BLACK = Color::BLACK;
const COLORREF ChipButton::CHIP_WHITE = Color::WHITE;
const COLORREF ChipButton::LINE_COLOR = Color::BLACK;


ChipButton::ChipButton(int x, int y, int btnSize, int chipSize) : x(x), y(y), btnSize(btnSize), chipSize(chipSize) {
    btnRect = {x, y, x + btnSize, y + btnSize };
    int dPlus = (btnSize + chipSize) / 2;
    int dMinus = (btnSize - chipSize) / 2;

    chipRect = {
            x + dMinus,
            y + dMinus,
            x + dPlus,
            y + dPlus
    };
}


void ChipButton::onPaint(HDC hdc) const {
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

bool ChipButton::containsPoint(int pX, int pY) {
    return (x <= pX && pX <= (x + btnSize)) &&
           (y <= pY && pY <= (y + btnSize));
}



// setters
void ChipButton::setBtnColor(COLORREF btnColor) { ChipButton::btnColor = btnColor; }
void ChipButton::setChipVisibility(bool showChip) { ChipButton::showChip = showChip; }
void ChipButton::setChipColor(COLORREF chipColor) { ChipButton::chipColor = chipColor; }

bool ChipButton::isChipVisible() const { return showChip; }

RECT ChipButton::getViewRect() const {
    return btnRect;
}




// старая функция
//int ChipButton::onPaint(LPDRAWITEMSTRUCT item) {
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







