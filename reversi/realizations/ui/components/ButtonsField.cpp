#include "includeAll.h"
#include "ButtonsField.h"


const int ButtonsField::BTN_FIELD_SIZE = 8;


ButtonsField::ButtonsField(int x, int y, int elementSize, int chipSize, int gap) : gap(gap), elementSize(elementSize) {
    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        buttons[i] = new ChipButton*[BTN_FIELD_SIZE];
    }

    startX = x;
    startY = y;
    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < BTN_FIELD_SIZE; ++j) {
            int btnX = x + j * (elementSize + gap);

            int btnY = y + i * (elementSize + gap);

            setButton(i, j, new ChipButton(btnX, btnY, elementSize, chipSize));
        }
    }
    int viewSize = BTN_FIELD_SIZE * elementSize + (BTN_FIELD_SIZE - 1) * gap;
    endX = startX + viewSize;
    endY = startY + viewSize;
}


void ButtonsField::onPaint(HDC hdc) const {
    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < BTN_FIELD_SIZE; ++j) {
            ChipButton* btn = getButton(i, j);
            btn->onPaint(hdc);
        }
    }
}

bool ButtonsField::onMouseMove(int pX, int pY) {
    if ((startX <= pX && pX <= endX) && (startY <= pY && pY <= endY)) { // if mouse inside field
        pair<int, int> indexes = findEnteredButton(pX, pY); // find a button below the mouse
        if (indexes.first == -1 && enteredBtnIndexes.first > -1) { // if previous btn is SMTH and current is NULL then clear
            if (listener != nullptr)
                listener->onMouseEscapedButton(this);
            enteredBtnIndexes = indexes;
            return true;
        } else if (indexes.first > -1 && (indexes.first != enteredBtnIndexes.first || indexes.second != enteredBtnIndexes.second)) {
            // if current is SMTH and previous is NOT THE SAME
            if (listener != nullptr)
                listener->onMouseEnteredButton(this, indexes.first, indexes.second);
            enteredBtnIndexes = indexes;
            return true;

        }
    } else if (enteredBtnIndexes.first > -1) { // clear if mouse escaped field
        if (listener != nullptr)
            listener->onMouseEscapedButton(this);
        enteredBtnIndexes = {-1, -1};
        return true;
    }
    return false;
}

bool ButtonsField::onClick(int pX, int pY) {
    pair<int, int> indexes = findEnteredButton(pX, pY);
    if (indexes.first > -1) {
        ChipButton* btn = getButton(indexes.first, indexes.second);
        if (listener != nullptr)
            listener->onClickOnButton(this, indexes.first, indexes.second);
//        btn->setChipVisibility(!btn->isChipVisible());
//        btn->setChipColor(ChipButton::CHIP_WHITE);
        return true;
    }
    return false;
}

pair<int, int> ButtonsField::findEnteredButton(int pX, int pY) {
    int i = -1, j = -1;
    int x1 = startX;
    int x2 = startX + elementSize;
    int y1 = startY;
    int y2 = startY + elementSize;
    int step = elementSize + gap;

    for (int k = 0; k < BTN_FIELD_SIZE; ++k) {
        if (x1 <= pX && pX <= x2) {
            j = k;
            break;
        }
        x1 += step;
        x2 += step;
    }
    for (int k = 0; k < BTN_FIELD_SIZE; ++k) {
        if (y1 <= pY && pY <= y2) {
            i = k;
            break;
        }
        y1 += step;
        y2 += step;
    }
    if (i == -1 || j == -1) {
        return {-1, -1};
    }
    return {i, j};

    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < BTN_FIELD_SIZE; ++j) {
            if (getButton(i, j)->containsPoint(pX, pY)) {
                return {i, j};
            }
        }
    }
    return {-1 ,-1};
}

ChipButton *ButtonsField::getButton(int i, int j) const { return buttons[j][i]; }

RECT ButtonsField::getViewRect() const {
    return RECT {startX, startY, endX, endY};
}
RECT ButtonsField::getChipViewRect(int i, int j) const {
    auto chipBtn = getButton(i, j);
    auto chipBtnRect = chipBtn->getChipRect();
    return chipBtnRect;
}

void ButtonsField::setListener(ButtonsFieldListener *listener) {
    ButtonsField::listener = listener;
}


// setters
void ButtonsField::setChipBlack(int i, int j) {
    getButton(i, j)->setChipColor(ChipButton::CHIP_BLACK);
    getButton(i, j)->setChipVisibility(true);
}
void ButtonsField::setChipWhite(int i, int j) {
    getButton(i, j)->setChipColor(ChipButton::CHIP_WHITE);
    getButton(i, j)->setChipVisibility(true);
}

void ButtonsField::setChipInvisible(int i, int j) {
    getButton(i, j)->setChipVisibility(false);
}

void ButtonsField::setButtonHighlighted(int i, int j) {
    getButton(i, j)->setBtnColor(ChipButton::BTN_HIGHLIGHTED);
}

void ButtonsField::setButtonSelected(int i, int j) {
    getButton(i, j)->setBtnColor(ChipButton::BTN_SELECTED);
}

void ButtonsField::setButtonClear(int i, int j) {
    getButton(i, j)->setBtnColor(ChipButton::BTN_CLEAR);
}


