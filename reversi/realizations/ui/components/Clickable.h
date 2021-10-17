#pragma once
#include "includeAll.h"

class Clickable : public Drawable {
public:
    // first - matched clicked area with component
    virtual bool onClick(int pX, int pY) = 0;
};