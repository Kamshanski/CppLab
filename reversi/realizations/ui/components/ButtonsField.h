#pragma once
#include "includeAll.h"


class ButtonsField : public Clickable {
public:
    // constants
    static const int BTN_FIELD_SIZE;
private:
    int startX, startY, endX, endY;
    int gap;
    // negatives mean mouse is not over a btn
    pair<int, int> enteredBtnIndexes {-1, -1};
    ChipButton*** buttons = new ChipButton**[BTN_FIELD_SIZE];
    ButtonFieldListener* listener = nullptr;

private:
    /** @return [-1, -1] if nothing found*/
    pair<int, int> findEnteredButton(int pX, int pY);

    void setButton(int i, int j, ChipButton* btn) { buttons[j][i] = btn; }

public:
    ButtonsField(int x, int y, int elementSize, int chipSize, int gap);

    void onPaint(HDC hdc) const override;
    RECT getViewRect() const override;

    bool onClick(int pX, int pY) override;

    bool onMouseMove(int pX, int pY);

    void setListener(ButtonFieldListener *listener);
    ChipButton* getButton(int i, int j) const;
};
