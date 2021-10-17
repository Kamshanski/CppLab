#include "includeAll.h"


using namespace std;
Field::Field(int size) : size(size) {
    field = new Chip**[size];
    for (int i = 0; i < size; ++i) {
        field[i] = new Chip*[size];
        for (int j = 0; j < size; ++j) {
            field[i][j] = Chip::NONE;
        }
    }

    initStartPositions();
}

void Field::initStartPositions() {
    setChip(3, 3, Chip::WHITE);
    setChip(4, 4, Chip::WHITE);
    setChip(4, 3, Chip::BLACK);
    setChip(3, 4, Chip::BLACK);
}

Chip* Field::getChip(int x, int y) const {
    return field[y][x];
}

void Field::setChip(int x, int y, Chip* chip) {
    field[y][x] = chip;
}

void Field::switchChip(int x, int y) {
    Chip* enemy = getChip(x, y)->getEnemy();
    setChip(x, y, enemy);
}

std::map<Chip*, int> Field::getStatistics() const {
    std::map<Chip*, int> map;
    for (auto chip: Chip::values()) {
        map[chip] = 0;
    }

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map[getChip(i, j)]++;
        }
    }

    return map;
}

Field *Field::getSnapshot() const {
    auto* snap = new Field(size);
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            snap->setChip(i, j, getChip(i, j));
        }
    }
    return snap;
}

void Field::clear() {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            setChip(i, j, Chip::NONE);
        }
    }
    initStartPositions();
}

std::ostream &operator<<(std::ostream &os, const Field &field) {
    for (int i = 0; i < field.size; ++i) {
        for (int j = 0; j < field.size; ++j) {
            os << std::setw(2) << chipToChar(field.getChip(i, j));
        }
        os << endl;
    }
    return os;
}

Field::~Field() {
    for (int i = 0; i < size; ++i) {
        delete[] field[i];
    }
    delete field;
    field = nullptr;
}

int Field::getSize() const {
    return size;
}



