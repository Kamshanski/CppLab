#pragma once
#include "includeAll.h"
struct ButtonFieldListenerImpl : public ButtonFieldListener {
private:
    ReversiEngine* engine;

public:
    ButtonFieldListenerImpl(ReversiEngine *engine);

    void setEnteredColors(ButtonsField* field, int i, int j) override;

    void setUnenteredColors(ButtonsField* field) override;

};

