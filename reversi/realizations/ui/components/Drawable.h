#pragma once
#include "includeAll.h"

class Drawable {
public:
    virtual void onPaint(HDC hdc) const = 0;

    virtual RECT getViewRect() const = 0;
};