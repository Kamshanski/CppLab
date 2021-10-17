#pragma once

#include "includeAll.h"
class Chip {
public:
    static Chip* const BLACK;
    static Chip* const WHITE;
    static Chip* const NONE;
    const std::string name;

    Chip* getEnemy();


    static std::array<Chip*, 3> values();
private:

    explicit Chip(std::string name);
    ~Chip() = default;
};


inline std::ostream& operator<<(std::ostream& os, const Chip& cat) {
    os << cat.name;
    return os;
}

