#pragma once
#include "includeAll.h"


class ButtonsField : public Clickable {
public:
    // constants
    static const int BTN_FIELD_SIZE;
private:
    int startX, startY, endX, endY;
    int gap, elementSize;
    // negatives mean mouse is not over a btn
    pair<int, int> enteredBtnIndexes {-1, -1};
    ChipButton*** buttons = new ChipButton**[BTN_FIELD_SIZE];
    ButtonsFieldListener* listener = nullptr;

private:
    /** @return [-1, -1] if nothing found*/
    pair<int, int> findEnteredButton(int pX, int pY);

    void setButton(int i, int j, ChipButton* btn) { buttons[j][i] = btn; }
    ChipButton* getButton(int i, int j) const;
public:
    ButtonsField(int x, int y, int elementSize, int chipSize, int gap);

    void onPaint(HDC hdc) const override;
    RECT getViewRect() const override;
    RECT getChipButtonViewRect(int i, int j) const;
    RECT getChipViewRect(int i, int j) const;

    bool onClick(int pX, int pY) override;

    bool onMouseMove(int pX, int pY);

    void setChipInvisible(int i, int j);
    void setChipBlack(int i, int j);
    void setChipWhite(int i, int j);

    void setButtonHighlighted(int i, int j);
    void setButtonSelected(int i, int j);
    void setButtonClear(int i, int j);

    void setListener(ButtonsFieldListener *listener);
};
