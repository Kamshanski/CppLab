#pragma once
#include "includeAll.h"
class ButtonsField;
struct ButtonFieldListener {
    virtual void setEnteredColors(ButtonsField* field, int i, int j) = 0;
    virtual void setUnenteredColors(ButtonsField* field) = 0;
};

