#pragma once
#include "includeAll.h"
struct RadioButtonGroupListener;

class RadioButtonGroup : public Clickable {
    static const COLORREF SELECTED;
    static const COLORREF CLEAR;
    static const COLORREF LINE_COLOR;
    static const int HORIZONTAL_GAP;
    static const int VERTICAL_GAP;
    static const int SIZE;
    static const int TEXT_WIDTH;


    vector<string> options;
    int x, y;
    int selectedIndex = 0;
    int startX, startY, endX, endY;
    RadioButtonGroupListener* listener = nullptr;

public:
    RadioButtonGroup(int x, int y, vector<string> options, int selectedIndex = 0);

    void setListener(RadioButtonGroupListener *listener);

    void onPaint(HDC hdc) const override;
    RECT getViewRect() const override;
    bool onClick(int pX, int pY) override;
    int getSelection() const;
    vector<string>& getOptions();
private:
    /** @return -1 if nothing found */
    int findOptionByCoords(int pX, int pY);

};


struct RadioButtonGroupListener {
    /** @return true if accept selection */
    virtual bool onSelected(int idNew, int idPrev, vector<string>& options) = 0;
};
