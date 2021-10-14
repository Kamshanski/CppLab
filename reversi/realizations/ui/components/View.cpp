#include "includeAll.h"

View::View(size_t id, Window* parent, int height, int width, int x, int y, string text)
        : id(id), parent(parent), height(height), width(width), x(x), y(y), text(std::move(text)) {
    descriptor = CreateWindow(
            this->className().c_str(),
            text.c_str(),
            windowFlags(),
            x, y,
            width, height,
            parent->getDescriptor(),
            (HMENU) id,
            NULL, NULL);

}

pair<int, int> View::getSize() const {
    return pair<int, int>(x, y);
}

bool View::setSize(int h, int w) {
    if (h < 0) return false;
    if (w < 0) return false;
    SetWindowPos(descriptor, NULL,
                 x, y,
                 width, height,
                 SWP_NOOWNERZORDER // Does not change the owner window's position in the Z order.
                 | SWP_NOMOVE // Retains the current position (ignores X and Y parameters).
    );
    this->height = h;
    this->width = w;
    return true;
}

/** @return Pair(height, width) */
pair<int, int> View::getPosition() const {
    return pair<int, int>(height, width);
}

bool View::setPosition(int x, int y) {
    SetWindowPos(descriptor, NULL,
                 x, y,
                 width, height,
                 SWP_NOOWNERZORDER // Does not change the owner window's position in the Z order.
                 | SWP_NOSIZE // Retains the current size (ignores the cx and cy parameters).
    );
    this->x = x;
    this->y = y;
    return true;
}

size_t View::getId() const {
    return id;
}

HWND View::getDescriptor() const {
    return descriptor;
}

Window* View::getParent() const {
    return parent;
}

long View::windowFlags() {
    return WS_VISIBLE | WS_CHILD | SS_CENTER;
}

string View::className() {
    return "STATIC";
}



