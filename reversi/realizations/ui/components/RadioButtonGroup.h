#pragma once
#include "includeAll.h"
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

public:
    RadioButtonGroup(int x, int y, vector<string> options, int selectedIndex = 0);

    void onPaint(HDC hdc) const;
    bool onClick(int pX, int pY);

private:
    /** @return -1 if nothing found */
    int findOptionByCoords(int pX, int pY);

};


/*
DrawText (hdc, TEXT ("Native Windows Development with CygWin and CLion."),
          -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER) ;
          */