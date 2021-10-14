#include "includeAll.h"


void Button::setListener(OnButtonListener* listener) {
    getParent()->addListener(listener);
    Button::listener = listener;
}
void Button::removeListener() {
    if (Button::listener != nullptr) {
        getParent()->removeListener(listener);
        delete Button::listener;
        Button::listener = nullptr;
    }
}


long Button::windowFlags() {
    return WS_CHILD|BS_PUSHBUTTON|WS_VISIBLE;
}

string Button::className() {
    return "button";
}


