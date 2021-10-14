#pragma once
#include "includeAll.h"
class Window;
class View {
    size_t id;
    HWND descriptor;
    Window* parent;
    int height, width, x, y;


protected:
    virtual string className();
    virtual long windowFlags();
    string text;
    View(size_t id, Window* parent, int height, int width, int x, int y, string text);
public:

    pair<int, int>  getSize() const;

    bool setSize(int h, int w);

    pair<int, int> getPosition() const;

    bool setPosition(int x, int y);

    size_t getId() const;

    HWND getDescriptor() const;

    Window* getParent() const;

};

