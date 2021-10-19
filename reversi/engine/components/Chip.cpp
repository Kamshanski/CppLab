#include "includeAll.h"
#include "Chip.h"


Chip::Chip(std::string name) : name(std::move(name)) {}

Chip* const Chip::BLACK = new Chip("BLACK");
Chip* const Chip::WHITE = new Chip("WHITE");
Chip* const Chip::NONE = new Chip("NONE");



Chip* Chip::getEnemy() {
    if (this == BLACK) return WHITE;
    if (this == WHITE) return BLACK;
    else throw IllegalChipException(this);

}

std::array<Chip*, 3> Chip::values() {
    return {BLACK, WHITE, NONE};
}

const char* Chip::cstr() {
    return name.c_str();
}

