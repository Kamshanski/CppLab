#pragma once
#include "includeAll.h"

class OnButtonListener;
class Window {
    HWND descriptor;
    vector<OnButtonListener*> btnListeners;
    int x, y, width, height;


public:
    void addListener(OnButtonListener* listener);
    void removeListener(OnButtonListener* listener);

    HWND getDescriptor() const;
};

