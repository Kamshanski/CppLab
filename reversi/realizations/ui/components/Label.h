#pragma once
#include "includeAll.h"
class Label : public View {
public:
    Label(size_t id, Window* parent, int height, int width, int x, int y, const string &text);

    string getText() const;

    void setText(string &text);


};

