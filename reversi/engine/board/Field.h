#pragma once
#include "includeAll.h"
class Field {

    Chip*** field;
    int size;

    void initStartPositions();
public:
    explicit Field(int size);
    ~Field();
    Chip * getChip(int x, int y) const;
    void setChip(int x, int y, Chip* chip);
    void switchChip(int x, int y);

    Field* getSnapshot() const;
    std::map<Chip*, int> getStatistics() const;
    void clear();

    int getSize() const;

    friend std::ostream &operator<<(std::ostream &os, const Field &field);
};


