#pragma once
#include "includeAll.h"
class Button : Label {
    OnButtonListener* listener = nullptr;
public:
    void setListener(OnButtonListener* listener);
    void removeListener();
    string className() override;
    long windowFlags() override;
};

