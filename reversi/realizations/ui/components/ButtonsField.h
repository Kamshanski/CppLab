#pragma once
#include "includeAll.h"


class ButtonsField {
public:
    // constants
    static const int BUTTON_FIELD_OFFSET;
    static const int BTN_FIELD_SIZE;
    static const int GAP;

private:
    int startX, startY, endX, endY;
    // negatives mean mouse is not over a btn
    pair<int, int> enteredBtnIndexes {-1, -1};
    Button*** buttons = new Button**[BTN_FIELD_SIZE];
    ButtonFieldListener* listener = nullptr;

private:
    /** @return [-1, -1] if nothing found*/
    pair<int, int> findEnteredButton(int pX, int pY);

    void setButton(int i, int j, Button* btn) { buttons[j][i] = btn; }

public:
    void onPaint(HDC hdc);
    bool onMouseMove(int pX, int pY);


public:
    ButtonsField(ButtonFieldListener* listener);

    Button* getButton(int i, int j) { return buttons[j][i]; }
};
