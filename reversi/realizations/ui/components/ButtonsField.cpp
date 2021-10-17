#include "includeAll.h"
#include "ButtonsField.h"


const int ButtonsField::BUTTON_FIELD_OFFSET = 60;
const int ButtonsField::BTN_FIELD_SIZE = 8;
const int ButtonsField::GAP = 2;



ButtonsField::ButtonsField(ButtonFieldListener* listener) : listener(listener){
    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        buttons[i] = new Button*[BTN_FIELD_SIZE];
    }

    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < BTN_FIELD_SIZE; ++j) {
            int x = BUTTON_FIELD_OFFSET + j * (Button::SIZE + GAP);
            if (j > 0) {
                x += (j - 1) * GAP;
            }

            int y = BUTTON_FIELD_OFFSET + i * (Button::SIZE + GAP);
            if (i > 0) {
                y += (i - 1) * GAP;
            }

            setButton(i, j, new Button(x, y));
        }
    }
    startX = startY = BUTTON_FIELD_OFFSET;
    endX = endY = BUTTON_FIELD_OFFSET + BTN_FIELD_SIZE * (Button::SIZE + ButtonsField::GAP);
}

void ButtonsField::onPaint(HDC hdc) {
    for (int i = 0; i < BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < BTN_FIELD_SIZE; ++j) {
            Button* btn = getButton(i, j);
            btn->onPaint(hdc);
        }
    }
}

bool ButtonsField::onMouseMove(int pX, int pY) {
    if ((startX <= pX && pX <= endX) && (startY <= pY && pY <= endY)) {
        pair<int, int> coords = findEnteredButton(pX, pY);
        if (coords.first == -1 && enteredBtnIndexes.first > -1) {
            if (listener != nullptr)
                listener->setUnenteredColors(this);
            enteredBtnIndexes = coords;
            return true;
            // TODO test
        } else if (coords.first > -1) {
            if (coords.first != enteredBtnIndexes.first ||
                coords.second != enteredBtnIndexes.second) {
                if (listener != nullptr)
                    listener->setEnteredColors(this, coords.first, coords.second);
                enteredBtnIndexes = coords;
                return true;
            }
        } else if (coords.first > -1 && enteredBtnIndexes.first > -1) {

        }
    } else if (enteredBtnIndexes.first > -1) {
        if (listener != nullptr)
            listener->setUnenteredColors(this);
        enteredBtnIndexes = {-1, -1};
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


