#include "includeAll.h"

void Window::addListener(OnButtonListener* listener) {
    btnListeners.push_back(listener);
}

void Window::removeListener(OnButtonListener *listener) {
    std::remove(btnListeners.begin(), btnListeners.end(), listener);
}

HWND Window::getDescriptor() const {
    return descriptor;
}
