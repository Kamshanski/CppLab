#pragma once

#include "includeAll.h"
class Chip {
public:

    const std::string name;

    Chip* getEnemy();

    static Chip *BLACK();
    static Chip *WHITE();
    static Chip *NONE();

    static std::array<Chip*, 3> values();
private:
    static Chip* _BLACK;
    static Chip* _WHITE;
    static Chip* _NONE;

    explicit Chip(std::string name);
    ~Chip() = default;
};


inline std::ostream& operator<<(std::ostream& os, const Chip& cat) {
    os << cat.name;
    return os;
}

