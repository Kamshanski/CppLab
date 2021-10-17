#pragma once
#include "includeAll.h"
struct RadioButtonGroupListener;

class RadioButtonGroup {
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

    void onPaint(HDC hdc) const;
    bool onClick(int pX, int pY);
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


/*
DrawText (hdc, TEXT ("Native Windows Development with CygWin and CLion."),
          -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
          */