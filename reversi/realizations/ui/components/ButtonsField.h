#pragma once
#include "includeAll.h"


class ButtonsField : public Drawable, public Clickable {
public:
    // constants
    static const int BUTTON_FIELD_OFFSET;
    static const int BTN_FIELD_SIZE;
    static const int GAP;

private:
    int startX, startY, endX, endY;
    // negatives mean mouse is not over a btn
    pair<int, int> enteredBtnIndexes {-1, -1};
    ChipButton*** buttons = new ChipButton**[BTN_FIELD_SIZE];
    ButtonFieldListener* listener = nullptr;

private:
    /** @return [-1, -1] if nothing found*/
    pair<int, int> findEnteredButton(int pX, int pY);

    void setButton(int i, int j, ChipButton* btn) { buttons[j][i] = btn; }

public:
    void onPaint(HDC hdc) const override;
    bool onMouseMove(int pX, int pY);
    bool onClick(int pX, int pY) override;


public:
    ButtonsField(ButtonFieldListener* listener);

    ChipButton* getButton(int i, int j) const;
};
