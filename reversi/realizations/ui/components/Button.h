#pragma once
#include "includeAll.h"

struct ButtonListener;

class Button: public Drawable, public Clickable {
    string text;

    RECT rect;
    COLORREF btnColor = Color::WHITE;
    COLORREF lineColor = Color::BLACK;
    COLORREF textColor = Color::BLACK;

    ButtonListener* listener = nullptr;
public:
    Button(int x, int y, int width, int height);

    bool onClick(int pX, int pY) override;

    void onPaint(HDC hdc) const override;

    void setListener(ButtonListener *listener);

    void setText(string text);
};

struct ButtonListener {
    /** @return true if accept selection */
    virtual bool onClicked() = 0;
};

