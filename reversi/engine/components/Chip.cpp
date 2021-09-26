#include "includeAll.h"

Chip::Chip(std::string name) : name(std::move(name)) {}

Chip* Chip::_BLACK = new Chip("BLACK");
Chip* Chip::_WHITE = new Chip("WHITE");
Chip* Chip::_NONE = new Chip("NONE");

Chip* Chip::getEnemy() {
    if (this == _BLACK) return _WHITE;
    if (this == _WHITE) return _BLACK;
    else throw IllegalChipException(this);

}

std::array<Chip*, 3> Chip::values() {
    return {_BLACK, _WHITE, _NONE};
}

Chip *Chip::BLACK() {
    return _BLACK;
}

Chip *Chip::WHITE() {
    return _WHITE;
}

Chip *Chip::NONE() {
    return _NONE;
}
