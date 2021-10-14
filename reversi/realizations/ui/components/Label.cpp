#include "includeAll.h"


Label::Label(size_t id, Window* parent, int height, int width, int x, int y, const string &text)
    : View(id,  parent, height, width, x, y, text) {}

string Label::getText() const {
    return text;
}

void Label::setText(string &text) {
    this->text = text;
    SetWindowText(getDescriptor(), text.c_str());
}
