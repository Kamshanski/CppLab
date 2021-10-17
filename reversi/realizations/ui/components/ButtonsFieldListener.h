#pragma once
#include "includeAll.h"
class ButtonsField;
struct ButtonsFieldListener {
    virtual void onMouseEnteredButton(ButtonsField* field, int i, int j) = 0;
    virtual void onMouseEscapedButton(ButtonsField* field) = 0;
    virtual void onClickOnButton(ButtonsField* field, int i, int j) = 0;
};

