#include "includeAll.h"
#include "ButtonsField.h"


const int ButtonsField::BTN_FIELD_SIZE = 8;


ButtonsField::ButtonsField(int x, int y, int elementSize, int chipSize, int gap) : gap(gap) {
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
    if ((startX <= pX && pX <= endX) && (startY <= pY && pY <= endY)) {
        pair<int, int> indexes = findEnteredButton(pX, pY);
        if (indexes.first == -1 && enteredBtnIndexes.first > -1) {
            if (listener != nullptr)
                listener->setUnenteredColors(this);
            enteredBtnIndexes = indexes;
            return true;
            // TODO test
        } else if (indexes.first > -1) {
            if (indexes.first != enteredBtnIndexes.first ||
                indexes.second != enteredBtnIndexes.second) {
                if (listener != nullptr)
                    listener->setEnteredColors(this, indexes.first, indexes.second);
                enteredBtnIndexes = indexes;
                return true;
            }
        } else if (indexes.first > -1 && enteredBtnIndexes.first > -1) {

        }
    } else if (enteredBtnIndexes.first > -1) {
        if (listener != nullptr)
            listener->setUnenteredColors(this);
        enteredBtnIndexes = {-1, -1};
        return true;
    }
    return false;
}

bool ButtonsField::onClick(int pX, int pY) {
    pair<int, int> indexes = findEnteredButton(pX, pY);
    if (indexes.first > -1) {
        ChipButton* btn = getButton(indexes.first, indexes.second);
        btn->setChipVisibility(!btn->isChipVisible());
        btn->setChipColor(ChipButton::CHIP_WHITE);
        return true;
    }
    return false;
}

pair<int, int> ButtonsField::findEnteredButton(int pX, int pY) {
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

void ButtonsField::setListener(ButtonFieldListener *listener) {
    ButtonsField::listener = listener;
}

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


