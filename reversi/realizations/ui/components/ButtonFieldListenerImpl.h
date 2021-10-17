#pragma once
#include "includeAll.h"
class ButtonFieldListenerImpl : public ButtonFieldListener {
    ReversiEngine* engine;

public:
    ButtonFieldListenerImpl(ReversiEngine *engine);

    void setEnteredColors(ButtonsField* field, int i, int j) override;

    void setUnenteredColors(ButtonsField* field) override;

};

