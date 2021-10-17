#include "includeAll.h"

void ButtonFieldListenerImpl::setEnteredColors(ButtonsField* field, int i, int j) {
    // TODO()
    this->setUnenteredColors(field);
    field->getButton(i, j)->setColor(Color::BLACK);

}

void ButtonFieldListenerImpl::setUnenteredColors(ButtonsField* field) {
    // TODO()
    for (int i = 0; i < ButtonsField::BTN_FIELD_SIZE; ++i) {
        for (int j = 0; j < ButtonsField::BTN_FIELD_SIZE; ++j) {
            field->getButton(i, j)->setColor(Color::YELLOW);
        }
    }
}

ButtonFieldListenerImpl::ButtonFieldListenerImpl(ReversiEngine *engine) : engine(engine) {}
